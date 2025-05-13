#include <cstddef>
#include <memory>
#include <utility>

namespace TupleItems {
    template <size_t ind, typename T>
    struct TupleUnit {
        T item;

        constexpr TupleUnit() = default;
        constexpr TupleUnit(T&& item) : item(item) {}

        constexpr T& get() {
            return item;
        }
    };

    template <size_t ind, typename... Tail>
    struct TupleSet;

    template <size_t ind>
    struct TupleSet<ind> {};

    template <size_t ind, typename T, typename... Tail>
    struct TupleSet<ind, T, Tail...> : TupleUnit<ind, T>, TupleSet<ind + 1, Tail...> {
        constexpr TupleSet() = default;
        
        template <typename Arg, typename... ArgTail>
        constexpr TupleSet(Arg&& arg, ArgTail&&... tail) : TupleUnit<ind, T>(std::forward<Arg>(arg)), 
        TupleSet<ind + 1, Tail...>(std::forward<ArgTail>(tail)...) {}
    };
}

namespace GetTypes {
    template <size_t ind, typename... Tail>
    struct impl;

    template <size_t ind, typename T, typename... Tail>
    struct impl<ind, T, Tail...> {
        using Type = typename impl<ind - 1, Tail...>::Type;
    };

    template <typename T,  typename... Tail>
    struct impl<0, T, Tail...> {
        using Type = T;
    };
}

template <typename... Types>
struct Tuple : TupleItems::TupleSet<0, Types...> {
    using Base = TupleItems::TupleSet<0, Types...>;
    
    constexpr Tuple() = default;

    template <typename... Args>
    constexpr Tuple(Args&&... args) : Base(std::forward<Args>(args)...) {}
};

template<size_t ind, typename... Types> requires(ind < sizeof...(Types))
decltype(auto) get(Tuple<Types...>& t) {
    return static_cast<TupleItems::TupleUnit<ind, typename GetTypes::impl<ind, Types...>::Type>&>(t).get();
}