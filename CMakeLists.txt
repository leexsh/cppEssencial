cmake_minimum_required(VERSION 3.19)
project(cppEssencical)

set(CMAKE_CXX_STANDARD 14)
add_executable(01_pointer cpp11AndAbove/01_pointer.cpp)
add_executable(02_thread cpp11AndAbove/02_thread.cpp)
add_executable(03_thread cpp11AndAbove/03_thread.cpp)
add_executable(cppEssencical cpp11AndAbove/04_mutex_01.cpp)