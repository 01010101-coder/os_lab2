cmake_minimum_required(VERSION 3.31)
project(os_lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(os_lab2 main.cpp
        include/array_processor.h
        src/array_processor.cpp)
