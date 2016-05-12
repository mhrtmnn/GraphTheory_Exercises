//
// Created by marco on 5/8/16.
//

#include "exercises.hpp"
#include "DirectedGraph.hpp"

#define SIZE_EX5 10000
#define ITERATIONS_EX5 300


void printMetrics(Graph& graph, Algorithms& alg)
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


void startEx5()
{
    //vector holding the number of components and the biggest one
    std::vector<std::pair<int, int>> resVec;
    resVec = std::vector<std::pair<int, int>>(ITERATIONS_EX5, std::pair<int, int>());

#ifdef MULTITHREAD_EX5
    //start threads
    std::thread  first(Ex5Worker, &resVec,   0,  75);
    std::thread second(Ex5Worker, &resVec,  75, 150);
    std::thread  third(Ex5Worker, &resVec, 150, 225);
    std::thread fourth(Ex5Worker, &resVec, 225, 301);

    //wait for threads to finish
    first.join();
    second.join();
    third.join();
    fourth.join();
#endif

#ifndef MULTITHREAD_EX5
    Ex5Worker(&resVec, 0, ITERATIONS_EX5);
#endif

    //create CSV from resVec
    createCSV(resVec);
}


//worker function for getting metrics of a randomly created graph
void Ex5Worker(std::vector<std::pair<int, int>>* resVec, int from, int to)
{
    const int n = SIZE_EX5;
    double p;

    Graph* graph = new Graph();
    Algorithms* alg = new Algorithms();

    //get number and max size of connected components for some possibilities
    for(int i=from; i<to; i++)
    {
        p = (double) (i+1) * 5 * pow(10, -6);
        graph->randomCreate(n, p);
        std::cout << i+1 << " graph created: ";

        std::pair<int, int> cmp = alg->findConnectedComponents(graph->getNumberVertices(), graph->getNeighbourhood());
        std::cout << cmp.first << " components, the largest being " << cmp.second << std::endl;

        (*resVec)[i] = cmp;
    }

    delete(graph);
}


//create a plottable CSV file from component vector
void createCSV(std::vector<std::pair<int, int>>& resVec)
{
    std::ofstream outfile("./plot.csv");
    const std::string delimiter = ";";
    int iteration = 1;

    outfile << "iteration" << delimiter << "numberComponents" + delimiter + "biggestComponent" << std::endl;
    for(std::pair<int, int> entry : resVec)
    {
        outfile << iteration << delimiter;
        outfile << entry.first << delimiter;
        outfile << entry.second << std::endl;
        iteration++;
    }

    outfile.close();
}


void startEx6()
{
    DirectedGraph dirGraph;
}
