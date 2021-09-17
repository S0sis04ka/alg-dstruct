cmake_minimum_required(VERSION 3.20)
project(gtests)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
include_directories(googletest/googlemock/include)
include_directories(../include)

enable_testing()

add_executable(
        tests
        unitTests.cpp
        ../src/list.c
)

target_link_libraries(
        tests
        gtest_main
)

target_link_libraries(
        tests
        gmock gmock_main
)