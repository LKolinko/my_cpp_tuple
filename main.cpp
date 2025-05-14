#include <tuple>
#include "tuple.hpp"
#include <string>
#include <iostream>


int main() {

    std::tuple<int, std::string, int> a1(1, "abacaba", 1);

    Tuple<int, int, int> a(1, 1, 1);
    Tuple<int, std::string, char> b(1, "abacaba", 1);
    
    if ((a <=> a) == std::strong_ordering::equal) {
        std::cout << "YES" << std::endl;
    }

    std::cout << sizeof(a) << ' ' << sizeof(a1) << std::endl;

    // std::tuple_size
    std::cout << std::tuple_size<decltype(a)>() << std::endl;

    // std::tuple_element
    static_assert(std::is_same_v<std::tuple_element_t<1, decltype(a1)>, std::string>);

    auto [e1, e2, e3] = a1;

    std::cout << e1 << ' ' << e2 << ' ' << e3 << std::endl;

    std::cout << a.get<1>() << std::endl;
    //a.get<1>() = "aboba";
    std::cout << a.get<1>() << std::endl;

    return 0;
}
