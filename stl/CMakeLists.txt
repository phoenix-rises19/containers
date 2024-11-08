CMAKE_MINIMUM_REQUIRED(VERSION 3.29)
PROJECT(stl)

set(CMAKE_CXX_STANDARD 23)

add_executable(vector vector.hpp
        main.cpp)
