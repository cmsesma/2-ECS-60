cmake_minimum_required(VERSION 3.8)
project(HW2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES priorityqueue.cpp priorityqueue.h buildheap.cxx createteams.cxx teamdata.cpp teamdata.h)
add_executable(HW2 ${SOURCE_FILES})