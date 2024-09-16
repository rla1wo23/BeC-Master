cmake_minimum_required(VERSION 3.10)

project(addExample)

set(CMAKE_CXX_STANDARD 11)

add_executable(addExampleExe main.cpp math_operations.cpp math_operations.h)