cmake_minimum_required(VERSION 3.13)

add_executable(sleepingBarber
    sleepingBarber.c
    barberWorkingThread.c
)

find_library(REQUIRED pthread)
target_link_libraries(sleepingBarber
    pthread
)