cmake_minimum_required(VERSION 3.7)
project(lab8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")

add_executable(server lab8_1.cpp)
add_executable(client lab8_2.cpp)

target_link_libraries(server rt pthread)
target_link_libraries(client rt pthread)
