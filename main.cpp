//============================================================================
// Name        : GraphTheoryEx1.cpp
// Author      : Marco Hartmann
// Version     :
// Copyright   : Your copyright notice
// Description : Exercise from Graph Theory
//============================================================================

#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <time.h>

#include "Graph.hpp"
#include "Algorithms.hpp"
#include "exercises.hpp"
#include "DirectedGraph.hpp"

int main()
{
    int c = 0;
    const std::string dataDir = "/home/marco/Documents/Projects/ClionProjects/GraphTheory-GIT/data/";
    const clock_t t = clock();

    Graph graph;
    Algorithms alg;

    std::cout << "choose Exercise: Ex1 [1]; Ex2 [2]; Ex3 [3]; Ex4 [4]; Ex5 [5]; Ex6 [6]; Test [7]" << std::endl;
    std::cin >> c;

    switch(c)
    {
        case 1:
            graph.loadGraph(dataDir + "graph15.txt");
            std::cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 2:
            graph.loadGraph(dataDir + "graph25.txt");
            std::cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 3:
            graph.loadGraph(dataDir + "graph34.txt");
            std::cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 4:
            startEx4(graph);
            std::cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 5:
            startEx5();
            break;
        case 6:
            startEx6(dataDir + "graph65.txt", alg);
            break;
        case 7:
            DirectedGraph digraph;
            digraph.loadGraph(dataDir + "test.txt");
            int dist = alg.dijkstra(0,4, &digraph);
        std::cout << dist << " is the distance from 0 to 4" << std::endl;
            break;
    }

    std::cout << "runtime: " <<  clock()-t << std::endl;
    usleep((__useconds_t) pow(10, 6));

    return 0;
}
