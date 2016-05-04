cmake_minimum_required(VERSION 3.5)
project(GraphTheoryEx4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -pthread -larmadillo -lopenblas -llapack")

set(SOURCE_FILES main.cpp algorithms.cpp Graph.cpp)
#set(SOURCE_FILES main.cpp Graph.cpp)
add_executable(GraphTheoryEx4 ${SOURCE_FILES})
