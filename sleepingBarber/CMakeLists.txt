cmake_minimum_required(VERSION 3.13)

find_library(REQUIRED pthread)
add_executable(sleepingBarber sleepingBarber.c)
target_link_libraries(sleepingBarber
    pthread
)