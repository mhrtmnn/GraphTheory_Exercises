//
// Created by marco on 5/8/16.
//

#ifndef GRAPHTHEORY_GIT_EXERCISES_HPP
#define GRAPHTHEORY_GIT_EXERCISES_HPP

#include "algorithms.hpp"
#include <thread>

void printMetrics(Graph&, algorithms&);
void startEx4(Graph&);
void startEx5(algorithms&);
void Ex5Worker(std::vector<std::pair<int, int>>*, algorithms*, int, int);

#endif //GRAPHTHEORY_GIT_EXERCISES_HPP
