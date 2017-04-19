cmake_minimum_required(VERSION 3.7)
project(Lab1_2)

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.8\\mingw53_32")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOLVER_PATH ./Model/Solver)
set(MATH_PATH ./Model/MyMath)

include_directories(${SOLVER_PATH} ${MATH_PATH})
set(SOLVER ${SOLVER_PATH}/ASolver.hpp
           ${SOLVER_PATH}/DoubleSolver.hpp Model/Solver/ComplexSolver.hpp)
set(MATH ${MATH_PATH}/Complex.hpp ${MATH_PATH}/Complex.cpp)
set(TESTS Tests/catch.hpp Tests/UnitTests.cpp)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SOLVER} ${MATH} mainwindow.h mainwindow.cpp)
add_executable(UnitTests ${TESTS} ${SOLVER} ${MATH})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
