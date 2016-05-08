//
// Created by marco on 5/8/16.
//

#include "exercises.hpp"

#define SIZE_EX5 10000

void printMetrics(Graph& graph, algorithms& alg)
{
    std::cout << graph.getAvgDeg() << " is the avg degree" << std::endl;
    std::cout << alg.calcTriangles(graph.getNumberVertices(), graph.getKnotMat()) << " triangles [Matrix]" << std::endl;
    std::cout << alg.calcTriangles2(graph.getNumberVertices(), graph.getNeighbourhood()) << " triangles [NeighVec]" << std::endl;

    alg.GreedyColoring(&graph);
    std::cout << graph.getNumberColors() << " colors needed using ascending vertex order" << std::endl;
    std::cout << std::endl << "min color number: X<=" << alg.executeRandomGreedy(&graph, 10) << std::endl;

    std::pair<int, int> comp = alg.findConnectedComponents(graph.getNumberVertices(), graph.getNeighbourhood());
    std::cout << "There are " << comp.first << " components, the largest being " << comp.second << std::endl;

}


void startEx4(Graph& graph)
{
    int n;
    double p;
    std::cout << "Poss: " ; std::cin >> p; std::cout << std::endl;
    std::cout << "Num Vert: "; std::cin >>n; std::cout << std::endl;
    graph.randomCreate(n, p);
}


void startEx5(algorithms& alg)
{
    //vector holding the number of components and the biggest one
    std::vector<std::pair<int, int>> resVec;
    resVec = std::vector<std::pair<int, int>>(SIZE_EX5, std::pair<int, int>());

#ifdef MULTITHREAD_EX5

    //start threads
    std::thread  first(Ex5Worker, &resVec, &alg,   0,  75);
    std::thread second(Ex5Worker, &resVec, &alg,  75, 150);
    std::thread  third(Ex5Worker, &resVec, &alg, 150, 225);
    std::thread fourth(Ex5Worker, &resVec, &alg, 225, 300);

    //wait for threads to finish
    first.join();
    second.join();
    third.join();
    fourth.join();
#endif

#ifndef MULTITHREAD_EX5
    Ex5Worker(&resVec, &alg, 0, 300);
#endif

    //TODO: plot resVec
}


void Ex5Worker(std::vector<std::pair<int, int>>* resVec, algorithms* alg, int from, int to)
{
    const int n = SIZE_EX5;
    double p;
    Graph* graph = new Graph();

    //get number and max size of connected components for some possibilities
    for(int i=from; i<to; i++)
    {
        p = (double) i * 5 * pow(10, -6);
        graph->randomCreate(n, p);
        std::cout << i << " graph created: ";

        std::pair<int, int> cmp = alg->findConnectedComponents(graph->getNumberVertices(), graph->getNeighbourhood());
        std::cout << cmp.first << " components, the largest being " << cmp.second << std::endl;

        (*resVec)[i] = cmp;
    }

    delete(graph);
}