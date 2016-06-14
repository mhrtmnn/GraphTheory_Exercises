//
// Created by marco on 5/8/16.
//

#ifndef GRAPHTHEORY_GIT_EXERCISES_HPP
#define GRAPHTHEORY_GIT_EXERCISES_HPP

#include "Algorithms.hpp"
#include <thread>
using namespace std;


void printMetrics(Graph&, Algorithms&);
void startEx4(Graph&);
void startEx5();
void startEx6(string, Algorithms&);
void startEx7(string, Algorithms&);
void Ex5Worker(vector<pair<int, int>>*, int, int);
void createCSV(vector<pair<int, int>> &);
void startEx10(Algorithms&);

#endif //GRAPHTHEORY_GIT_EXERCISES_HPP
