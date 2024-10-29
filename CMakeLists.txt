cmake_minimum_required(VERSION 3.13)
project(sort)

add_library(sortLib
    helper.c
    tests.c
    qsort.c
    mergeSort.c
    heapSort.c
)

add_executable(sortTesting sortTesting.c)
target_link_libraries(sortTesting sortLib)


set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")