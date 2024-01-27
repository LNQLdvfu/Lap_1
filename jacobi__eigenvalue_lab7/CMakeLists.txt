cmake_minimum_required(VERSION 3.22)
project(jacobi__eigenvalue)

set(CMAKE_CXX_STANDARD 23)

add_executable(jacobi__eigenvalue main.cpp matrix.h matrix.cpp)
