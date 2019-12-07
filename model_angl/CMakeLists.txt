cmake_minimum_required(VERSION 3.3)
project(model_angl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp grid.cpp grid.hpp cell.cpp cell.hpp)
add_executable(model_angl ${SOURCE_FILES})