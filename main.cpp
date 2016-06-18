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
#include <iomanip>

#include "Graph.hpp"
#include "graphAlgorithms.hpp"
#include "exercises.hpp"
#include "DirectedGraph.hpp"
#include "scheduler.hpp"

using namespace std;


int main()
{
    int c = 0;
    const string dataDir = "/home/marco/Documents/Projects/ClionProjects/GraphTheory-GIT/data/";
    const clock_t t = clock();

    Graph graph;
    graphAlgorithms alg;

    cout << "choose Exercise: Ex1 [1]; Ex2 [2]; Ex3 [3]; Ex4 [4]; Ex5 [5];" << endl;
    cout << "                 Ex6 [6]; Ex7 [7]; Test [8]; OnlineTestScheduler [9]; Ex10 [10]" << endl;
    cout << "choice >>";
    cin >> c;

    switch(c)
    {
        case 1:
        {
            graph.loadGraph(dataDir + "graph15.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        }
        case 2:
        {
            graph.loadGraph(dataDir + "graph25.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        }
        case 3:
        {
            graph.loadGraph(dataDir + "graph34.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        }
        case 4:
        {
            startEx4(graph);
            cout << "\ngraph loaded\n";
            printMetrics(graph, alg);
            break;
        }
        case 5:
        {
            startEx5();
            break;
        }
         case 6:
            startEx6(dataDir + "graph65.txt", alg);
            break;
        case 7:
        {
            startEx7(dataDir + "graph75.txt", alg);
            break;
        }
        case 8:
        {
            DirectedGraph digraph;
            digraph.loadGraph(dataDir + "test.txt");
            double dist = alg.getMSTWeightKruskal(&digraph);
            cout << std::setprecision(12) << " W(MST) = " << dist << endl;
            break;
        }
        case 9:
        {
            scheduler sched;
            sched.loadSchedule();
            cout << "min penalty: " << sched.minPenalty() << endl;
            break;
        }
        case 10:
        {
            startEx10(alg);
        }
    }

    cout << "runtime: " <<  clock()-t << endl;
    usleep((__useconds_t) pow(10, 6));

    return 0;
}
