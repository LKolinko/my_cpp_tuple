cmake_minimum_required(VERSION 3.28)

project(recursive_tuple)

set(CMAKE_CXX_FLAGS "-std=c++2c")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++-20")
set(CMAKE_C_COMPILER "/usr/bin/clang-20")

add_executable(recursive_tuple main.cpp)