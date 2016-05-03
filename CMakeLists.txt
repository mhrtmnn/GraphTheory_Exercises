cmake_minimum_required(VERSION 3.5)
project(GraphTheoryEx4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Og")

set(SOURCE_FILES main.cpp algorithms.cpp Graph.cpp)
add_executable(GraphTheoryEx4 ${SOURCE_FILES})