set(CMAKE_MINIMUM_REQUIRED_VERSION 3.20)
set(CMAKE_C_STANDARD 99)

project(Lab_D)

add_subdirectory(gtests)

add_executable(
        program
        main.c
        color.c
)