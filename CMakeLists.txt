cmake_minimum_required(VERSION 3.10)
project(HW4_AVL CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
add_executable(HW4_AVL
        AVL.h
        main.cpp)

set_target_properties(HW4_AVL PROPERTIES LINKER_LANGUAGE CXX)
