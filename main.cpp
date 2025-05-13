#include <tuple>
#include "tuple.hpp"
#include <string>
#include <iostream>


int main() {

    std::tuple<int, std::string, int> a1(1, "abacaba", 1);

    Tuple<int, std::string, int> a(1, "abacaba", 1);

    std::cout << sizeof(a) << ' ' << sizeof(a1) << std::endl;

    // std::tuple_size
    std::cout << std::tuple_size<decltype(a)>() << std::endl;

    // std::tuple_element
    static_assert(std::is_same_v<std::tuple_element_t<1, decltype(a1)>, std::string>);

    auto [e1, e2, e3] = a1;

    std::cout << e1 << ' ' << e2 << ' ' << e3 << std::endl;

    std::cout << get<1>(a) << std::endl;
    get<1>(a) = "aboba";
    std::cout << get<1>(a) << std::endl;

    return 0;
}
