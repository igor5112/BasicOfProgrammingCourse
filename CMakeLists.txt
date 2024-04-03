cmake_minimum_required(VERSION 3.26)
project(untitled4 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled4 main.c
        libs/data_structures/vector/vector.h
        libs/data_structures/vector/vector.c
        libs/data_structures/vector/main.c
        libs/data_structures/matrix/matrix.h
        libs/data_structures/matrix/matrix.c
)
