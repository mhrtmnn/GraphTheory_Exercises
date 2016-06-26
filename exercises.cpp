//
// Created by marco on 5/8/16.
//

#include "exercises.hpp"
#include "knapsackProblem.hpp"

#define SIZE_EX5 10000
#define ITERATIONS_EX5 300

using namespace std;


void printMetrics(Graph& graph, graphAlgorithms& alg)
{
    cout << "Search for triangles? [v] yes, vector method; [m] yes matrix method;";
    cout << "[b] yes, both; [n] don't search" << endl;

    char c;
    cin >> c;
    switch(c)
    {
        case 'v':
            cout << alg.calcTriangles2(graph.getNumberVertices(), graph.getNeighbourhood()) << " triangle(s) [NeighVec]" << endl;
            break;
        case 'm':
            cout << alg.calcTriangles(graph.getNumberVertices(), graph.getKnotMat()) << " triangles [Matrix]" << endl;
            break;
        case 'b':
            cout << alg.calcTriangles(graph.getNumberVertices(), graph.getKnotMat()) << " triangles [Matrix]" << endl;
            cout << alg.calcTriangles2(graph.getNumberVertices(), graph.getNeighbourhood()) << " triangles [NeighVec]" << endl;
            break;
        case 'n':
            break;
        default:
            break;
    }

    cout << graph.getAvgDeg() << " is the avg degree" << endl;

    alg.GreedyColoring(&graph);
    cout << graph.getNumberColors() << " colors needed using ascending vertex order" << endl;
    cout << endl << "min color number: X<=" << alg.executeRandomGreedy(&graph, 10) << endl;

    pair<int, int> comp = alg.findConnectedComponents(graph.getNumberVertices(), graph.getNeighbourhood());
    cout << "There are " << comp.first << " components, the largest being " << comp.second << endl;
}


void startEx4(Graph& graph)
{
    int n;
    double p;
    cout << "Poss: " ; cin >> p; cout << endl;
    cout << "Num Vert: "; cin >>n; cout << endl;
    graph.randomCreate(n, p);
}


void startEx5()
{
    //vector holding the number of components and the biggest one
    vector<pair<int, int>> resVec;
    resVec = vector<pair<int, int>>(ITERATIONS_EX5, pair<int, int>());

#ifdef MULTITHREAD_EX5
    //start threads
    thread  first(Ex5Worker, &resVec,   0,  75);
    thread second(Ex5Worker, &resVec,  75, 150);
    thread  third(Ex5Worker, &resVec, 150, 225);
    thread fourth(Ex5Worker, &resVec, 225, 301);

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
void Ex5Worker(vector<pair<int, int>>* resVec, int from, int to)
{
    const int n = SIZE_EX5;
    double p;

    Graph* graph = new Graph();
    graphAlgorithms* alg = new graphAlgorithms();

    //get number and max size of connected components for some possibilities
    for(int i=from; i<to; i++)
    {
        p = (double) (i+1) * 5 * pow(10, -6);
        graph->randomCreate(n, p);
        cout << i+1 << " graph created: ";

        pair<int, int> cmp = alg->findConnectedComponents(graph->getNumberVertices(), graph->getNeighbourhood());
        cout << cmp.first << " components, the largest being " << cmp.second << endl;

        (*resVec)[i] = cmp;
    }

    delete(graph);
}


//create a plottable CSV file from component vector
void createCSV(vector<pair<int, int>>& resVec)
{
    ofstream outfile("./plot.csv");
    const string delimiter = ";";
    int iteration = 1;

    outfile << "iteration" << delimiter << "numberComponents" + delimiter + "biggestComponent" << endl;
    for(pair<int, int> entry : resVec)
    {
        outfile << iteration << delimiter;
        outfile << entry.first << delimiter;
        outfile << entry.second << endl;
        iteration++;
    }

    outfile.close();
}


void startEx6(string path, graphAlgorithms& alg)
{
    DirectedGraph diGraph;
    diGraph.loadGraph(path);
    float dist = alg.dijkstra(0, 1, &diGraph);
    cout << "dist(1,2) = " << dist << endl;
}


void startEx7(string path, graphAlgorithms& alg)
{
    DirectedGraph diGraph;
    diGraph.loadGraph(path);

    double weight = alg.getMSTWeightKruskal(&diGraph);
    cout << "W(MST) = " << weight << endl;
}

void startEx10(graphAlgorithms& alg)
{
    Graph graph;
    double p;
    int n;

    cout << "enter p >>";
    cin >> p;
    cout << "\nenter n >>";
    cin >> n;
    graph.randomCreate(n, p);

    vector<edge> mEdges = alg.GreedyMatching(graph);

    cout << "Matching contains " << mEdges.size() << " edges." << endl;
    cout << "Total edges:  " << graph.getNumberEdges();
    cout << " and " << graph.getNumberVertices() << " vertices." << endl;
}


void startEx11(ComplexityAlgorithms &alg)
{
    int n = 5, k = 3, m = 3, t = 3;

    cout << "\nenter k (SAT type) >>";
    cin >> k;
    cout << "\nenter m (number clauses) >>";
    cin >> m;
    cout << "\nenter n (number literals) >>";
    cin >> n;
    cout << "\nenter t (loop iterations) >>";
    cin >> t;

    struct satFormula S;
    S.k = k;
    S.m = m;
    S.n = n;

    S.xVal = new bool[n];

    //randomly assign literals and their signs
    for(int i=0; i<m; i++)
    {
        S.xData.push_back(vector<pair<int, bool>>());
        for(int j=0; j<k; j++)
        {
            S.xData[i].push_back(pair<int, bool>());
            S.xData[i][j].first = rand() % n;
            S.xData[i][j].second = rand() % 2;
        }
    }

    printSAT(&S);

    if( alg.randomWalk(&S, t) )
    {
        cout << "satisfiable! with:" << endl;
        printVal(&S);
    }
    else
    { cout << "satisfiable!" << endl; }

    delete S.xVal;
}

void printSAT(struct satFormula *S)
{
     for(int i=0, m=S->m; i<m; i++)
     {
         cout << "(";
         for(int j=0, k=S->k; j<k; j++)
         {
             cout << (S->xData[i][j].second?"NOT ":"") << "X{" << S->xData[i][j].first << "}" << (j==k-1?")":" V ");
         }
         if(i<m-1)
         { cout << " A " ; }
     }
    cout << endl;

    cout << "with initial truth values: " << endl;
    printVal(S);
}

void printVal(struct satFormula* S)
{
    for(int i=0; i<S->n; i++)
    {
        cout << (S->xVal[i]?"w":"f") << " ";
    }
    cout << endl;
}

void startEx13(string s)
{
    knapsackProblem kp;
    kp.parseFile(s);
    auto v = kp.solveKP();

    for(auto e : v)
    {
        cout << "object " << e << " in knapsack" << endl;
    }

}
