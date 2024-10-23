cmake_minimum_required(VERSION 3.13)
project(sort)

add_library(sort_lib
    helper.c
    tests.c
    qsort.c
)

add_executable(sort main.c)
target_link_libraries(sort sort_lib)
