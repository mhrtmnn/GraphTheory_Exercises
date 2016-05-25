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
using namespace std;


int main()
{
    int c = 0;
    const string dataDir = "/home/marco/Documents/Projects/ClionProjects/GraphTheory-GIT/data/";
    const clock_t t = clock();

    Graph graph;
    Algorithms alg;

    cout << "choose Exercise: Ex1 [1]; Ex2 [2]; Ex3 [3]; Ex4 [4]; Ex5 [5]; Ex6 [6]; Ex7 [7]; Test [8]" << endl;
    cin >> c;

    switch(c)
    {
        case 1:
            graph.loadGraph(dataDir + "graph15.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 2:
            graph.loadGraph(dataDir + "graph25.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 3:
            graph.loadGraph(dataDir + "graph34.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 4:
            startEx4(graph);
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        case 5:
            startEx5();
            break;
        case 6:
            startEx6(dataDir + "graph65.txt", alg);
            break;
        case 7:
            startEx7(dataDir + "graph75.txt", alg);
            break;
        case 8:
            DirectedGraph digraph;
            digraph.loadGraph(dataDir + "test.txt");
            float dist = alg.getMSTWeightKruskal(&digraph);
            cout << dist << " W(MST) = " << endl;
            break;
    }

    cout << "runtime: " <<  clock()-t << endl;
    usleep((__useconds_t) pow(10, 6));

    return 0;
}
