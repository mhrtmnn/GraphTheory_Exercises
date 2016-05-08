//
// Created by marco on 5/8/16.
//

#ifndef GRAPHTHEORY_GIT_EXERCISES_HPP
#define GRAPHTHEORY_GIT_EXERCISES_HPP

#include "Algorithms.hpp"
#include <thread>

void printMetrics(Graph&, Algorithms&);
void startEx4(Graph&);
void startEx5();
void Ex5Worker(std::vector<std::pair<int, int>>*, int, int);

#endif //GRAPHTHEORY_GIT_EXERCISES_HPP
