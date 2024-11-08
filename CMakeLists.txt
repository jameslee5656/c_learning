cmake_minimum_required(VERSION 3.13)
project(c_learning)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(sort)
add_subdirectory(sleepingBarber)