cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
include_directories(include)

add_executable(lab1 src/lab1.c src/list.c)