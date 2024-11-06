cmake_minimum_required(VERSION 3.13)
project(sort)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(sortLib
    helper.c
    unitTests.c
    qsort.c
    mergeSort.c
    heapSort.c
    insertionSort.c
    selectionSort.c
    radixSort.c
)

add_executable(sortTesting sortTesting.c)
target_link_libraries(sortTesting sortLib)


# sortGUnitTesting
include_directories(.)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(sortGUnitTesting sortGUnitTesting.cpp)
target_link_libraries(sortGUnitTesting
    sortLib
    ${GTEST_BOTH_LIBRARIES}
)
gtest_discover_tests(sortGUnitTesting)

# sleepingBarber
add_subdirectory(sleepingBarber)