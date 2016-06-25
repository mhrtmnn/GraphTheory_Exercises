//
// Created by marco on 5/8/16.
//

#ifndef GRAPHTHEORY_GIT_EXERCISES_HPP
#define GRAPHTHEORY_GIT_EXERCISES_HPP

#include "graphAlgorithms.hpp"
#include "ComplexityAlgorithms.hpp"
#include <thread>
using namespace std;


void printMetrics(Graph&, graphAlgorithms&);
void startEx4(Graph&);
void startEx5();
void startEx6(string, graphAlgorithms&);
void startEx7(string, graphAlgorithms&);
void Ex5Worker(vector<pair<int, int>>*, int, int);
void createCSV(vector<pair<int, int>> &);
void startEx10(graphAlgorithms&);
void startEx11(ComplexityAlgorithms &);
void printSAT(struct satFormula*);
void printVal(struct satFormula*);
void startEx13();



#endif //GRAPHTHEORY_GIT_EXERCISES_HPP
