cmake_minimum_required(VERSION 3.4)
project(GraphTheory-GIT)

set(CUST_LIBS "-L /home/marco/.local/share/lib/lib/libarmadillo.so.6.700.6 -pthread")
set(CUST_INCL "-I /home/marco/.local/share/lib/include ")


################################BUILD CONFIGs################################
set(CUST_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic -g")
#set(CUST_CXX_FLAGS "-std=c++11 -march=native -O3")
#set(CUST_CXX_FLAGS "-std=c++11 -Wall -Wextra -pg")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUST_CXX_FLAGS} ${CUST_LIBS} ${CUST_INCL}")

set(SOURCE_FILES main.cpp graphAlgorithms.cpp ComplexityAlgorithms.cpp exercises.cpp)
set(SOURCE_FILES ${SOURCE_FILES} Graph.cpp BaseGraph.cpp DirectedGraph.cpp)
set(SOURCE_FILES ${SOURCE_FILES} task.cpp scheduler.cpp knapsackProblem.cpp)

add_executable(GraphTheory-GIT ${SOURCE_FILES})
