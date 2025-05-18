#pragma once
#include <cstddef>
#include <memory>
#include <utility>
#include <type_traits>

namespace TupleItems {
    template <size_t ind, typename T>
    struct TupleUnit {
        T item;

        constexpr TupleUnit() = default;
        constexpr TupleUnit(T&& item) : item(item) {}

        constexpr T& get() {
            return item;
        }
        
        constexpr const T& get() const {
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

template <typename... Types>
struct Tuple : TupleItems::TupleSet<0, Types...> {
    using Base = TupleItems::TupleSet<0, Types...>;
    
    constexpr Tuple() = default;

    template <typename... Args>
    constexpr Tuple(Args&&... args) : Base(std::forward<Args>(args)...) {}

    template <size_t ind> requires(ind < sizeof...(Types))
    decltype(auto) get() {
        return static_cast<TupleItems::TupleUnit<ind, Types...[ind]>&>(*this).get();
    }

    template <size_t ind> requires(ind < sizeof...(Types))
    decltype(auto) get() const {
        return static_cast<const TupleItems::TupleUnit<ind, Types...[ind]>&>(*this).get();
    }
};

template <typename... FTypes, typename... STypes>
requires (
    sizeof...(FTypes) == sizeof...(STypes) &&
    ([] <class A, class B> (std::type_identity<A>, std::type_identity<B>) { 
        return requires (A a, B b) { a <=> b; };
    } (std::type_identity<FTypes>{}, std::type_identity<STypes>{}) && ...)
)
constexpr std::strong_ordering operator<=>(const Tuple<FTypes...>& a, const Tuple<STypes...>& b) {
    std::strong_ordering result = std::strong_ordering::equal;
    [&] <size_t... Ind> (std::index_sequence<Ind...>) {
        ([&] <size_t ind> (std::index_sequence<ind>) {
            if (result == std::strong_ordering::equal) {
                result = (a.template get<ind>() <=> b.template get<ind>());
            }
        } (std::index_sequence<Ind>()), ...);
    } (std::make_index_sequence<sizeof...(FTypes)>());
    return result;
}

template <typename... Types>
struct std::tuple_size<Tuple<Types...>> : public std::integral_constant<size_t, sizeof...(Types)> {};

template <size_t ind, typename... Types>
struct std::tuple_element<ind, Tuple<Types...>> {
    using Type = Types...[ind];
};
