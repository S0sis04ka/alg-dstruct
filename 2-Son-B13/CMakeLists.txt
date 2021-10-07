cmake_minimum_required(VERSION 3.20)
project(2_Son_B13 C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(2_Son_B13 src/main.c src/memallocator.c)
