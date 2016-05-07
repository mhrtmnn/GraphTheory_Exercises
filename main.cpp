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
#include "algorithms.hpp"

int main()
{
    int c = 0;
    const std::string dataDir = "/home/marco/Documents/Projects/ClionProjects/GraphTheory-GIT/data/";

    Graph graph;
    algorithms alg;

    std::cout << "choose Ex" << std::endl;
    std::cin >> c;
    switch(c)
    {
        case 1:
            graph.loadGraph(dataDir + "graph15.txt");
            break;
        case 2:
            graph.loadGraph(dataDir + "graph25.txt");
            break;
        case 3:
            graph.loadGraph(dataDir + "graph34.txt");
            break;
        case 4:
            int n;
            double p;
            std::cout << "Poss: " ; std::cin >> p; std::cout << std::endl;
            std::cout << "Num Vert: "; std::cin >>n; std::cout << std::endl;
            graph.randomCreate(n, p);
            break;
        case 5:
            graph.loadGraph(dataDir + "test.txt");
            break;
    }

    std::cout << "\ngraph loaded\n";

    clock_t t = clock();

    std::cout << graph.getAvgDeg() << " is the avg degree" << std::endl;
    std::cout <<  alg.calcTriangles(graph.getNumberVertices(), graph.getKnotMat()) << " triangles [Matrix]" << std::endl;
    std::cout << alg.calcTriangles2(graph.getNumberVertices(), graph.getNeighbourhood()) << " triangles [NeighVec]" << std::endl;

    alg.GreedyColoring(&graph);
    std::cout << graph.getNumberColors() << " colors needed using ascending vertex order" << std::endl;
    std::cout << std::endl << "min color number: X<=" << alg.executeRandomGreedy(&graph, 10) << std::endl;

    std::pair<int, int> comp = alg.findConnectedComponents(graph.getNumberVertices(), graph.getNeighbourhood());
    std::cout << "There are " << comp.first << " components, the largest being " << comp.second << std::endl;

    std::cout << "runtime: " <<  clock()-t << std::endl;
    usleep((__useconds_t) pow(10, 6));
    return 0;
}
