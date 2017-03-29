cmake_minimum_required(VERSION 3.6)
project(ShitCode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -l ncurses")

set(SOURCE_FILES main.cpp TypeManipulations.cpp TypeManipulations.h)
add_executable(ShitCode ${SOURCE_FILES})