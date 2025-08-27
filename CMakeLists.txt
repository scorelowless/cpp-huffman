cmake_minimum_required(VERSION 4.0)
project(cpp_huffman)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_huffman
        main.cpp
        functions.cpp
        functions.h
        node.cpp
        node.h
        node_comparator.cpp
        node_comparator.h
        compressed_string_builder.cpp
        compressed_string_builder.h)
