#include <tuple>
#include "tuple.hpp"
#include <string>
#include <iostream>


int main() {

    std::tuple<int, std::string, int> a1(1, "abacaba", 1);

    Tuple<int, std::string, int> a(1, "abacaba", 1);

    std::cout << sizeof(a) << ' ' << sizeof(a1) << std::endl;

    std::cout << get<1>(a) << std::endl;
    get<1>(a) = "aboba";
    std::cout << get<1>(a) << std::endl;

    return 0;
}
