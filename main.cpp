//============================================================================
// Name        : GraphTheoryEx1.cpp
// Author      : Marco Hartmann
// Version     :
// Copyright   : Your copyright notice
// Description : Exercise 1 from Graph Theory
//============================================================================

#include <iostream>
#include <cstddef>
#include <unistd.h>

#include "Graph.hpp"
#include "algorithms.hpp"

using namespace std;
#define SIZE 1000
#define POSS 0.001


int main(int argc, char *argv[])
{
    Graph graph;
    algorithms alg = algorithms();

    graph.create(SIZE, POSS);
    std::cout << "\ngraph loaded\n";

    std::cout << graph.getAvgDeg() << " is the avg degree" << std::endl;
    std::cout << graph.getTriangles() << " triangles" << std::endl;

    alg.GreedyColoring(&graph);
    graph.printColor();
    std::cout << std::endl << "min color number: " <<  alg.randomGreedy(&graph, 100) << std::endl;
    std::cout << graph.getNumberColors() << " colors needed in ascending order" << std::endl;

    usleep((__useconds_t) pow(10, 6));
    return 0;
}
