//============================================================================
// Name        : GraphTheoryEx1.cpp
// Author      : Marco Hartmann
// Version     :
// Copyright   : Your copyright notice
// Description : Exercise from Graph Theory
//============================================================================

#include <iostream>
#include <cstddef>
#include <iomanip>

#include "Graph.hpp"
#include "exercises.hpp"
#include "scheduler.hpp"

using namespace std;


int main()
{
    int c = 11;
    const string dataDir = "/home/marco/Documents/Projects/ClionProjects/GraphTheory-GIT/data/";
    const clock_t t = clock();

    Graph graph;
    graphAlgorithms gAlg;
    ComplexityAlgorithms cAlg;

    cout << "choose Exercise: Ex1 [1]; Ex2 [2]; Ex3 [3]; Ex4 [4]; Ex5 [5];" << endl;
    cout << "                 Ex6 [6]; Ex7 [7]; Test [8]; OnlineTestScheduler [9]; Ex9 [10]" << endl;
    cout << "                 Ex10 [11]; Onlinetest 10 [12]; Ex11 [13]" << endl;
    cout << "choice >>";
    cin >> c;

    switch(c)
    {
        case 1:
        {
            graph.loadGraph(dataDir + "graph15.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, gAlg);
            break;
        }
        case 2:
        {
            graph.loadGraph(dataDir + "graph25.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, gAlg);
            break;
        }
        case 3:
        {
            graph.loadGraph(dataDir + "graph34.txt");
            cout << "\ngraph loaded\n";
            printMetrics(graph, gAlg);
            break;
        }
        case 4:
        {
            startEx4(graph);
            cout << "\ngraph loaded\n";
            printMetrics(graph, gAlg);
            break;
        }
        case 5:
        {
            startEx5();
            break;
        }
         case 6:
            startEx6(dataDir + "graph65.txt", gAlg);
            break;
        case 7:
        {
            startEx7(dataDir + "graph75.txt", gAlg);
            break;
        }
        case 8:
        {
            DirectedGraph digraph;
            digraph.loadGraph(dataDir + "test.txt");
            double dist = gAlg.getMSTWeightKruskal(&digraph);
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
            startEx10(gAlg);
        }
        case 11:
        {
            startEx11(cAlg);
        }
        case 12:
        {
            Graph g;
            g.loadGraph(dataDir + "onlinetest10.txt");
            auto M = gAlg.GreedyMatchingAsc(g);
            cout << "size of matching: " << M.size() << endl;
        }
        case 13:
        {
            startEx13();
        }
        default:
            break;
    }

    cout << "runtime: " <<  clock()-t << endl;

    return 0;
}
