//
// Created by marco on 4/20/16.
//

#include "Algorithms.hpp"
#define FLOAT_INF numeric_limits<float>::infinity()
using namespace std;



//PROTOTYPES
void multWorker(int, int, arma::Mat<short>*, arma::Mat<short>*);

//apply greedy alg to n randomly selected knot orders
int Algorithms::executeRandomGreedy(Graph *g, int n)
{
    //run greedy with randomly selected knot orders
    vector<int> num = vector<int>(g->getNumberVertices());
    iota(num.begin(), num.end(), 0);
    int minColor = 1000;
    int currColor;
    for(int i=0; i<n; i++)
    {
        currColor = GreedyColoringCustom(g, &num);
        random_shuffle ( num.begin(), num.end() );

        cout << currColor << "|" ;
        if(currColor<minColor)
        { minColor = currColor; }
    }

    return minColor;
}

//implementation of the greedy coloring alg: colors vertices in a custom order
int Algorithms::GreedyColoringCustom(Graph *g, vector<int> *custOrder)
{
    //map holding the knot<->color mapping
    map<int, int> coloringMap;

    long numKnot = g->getNumberVertices();
    int biggestColor = 0;
    int newColor;

    for (int i = 0; i < numKnot; i++)
    {
        int k = (*custOrder)[i];

        //set of already used colors
        set<int> usedColorSet;

        for (int j = 0; j < i; j++)
        {
            //N := N U c(v(j))
            if (g->getEntry(j, k))
            { usedColorSet.insert(coloringMap.at(j)); }
        }

        newColor = getMinFreeColor(&usedColorSet, numKnot);
        if (newColor > biggestColor)
        { biggestColor = newColor; }

        coloringMap.insert(pair<key_t, int>(i, newColor));
    }

    return biggestColor;
}

//implementation of the greedy coloring alg: colors vertices in ascending order
void Algorithms::GreedyColoring(Graph* g)
{
    //map holding the knot<->color mapping
    map<int, int> coloringMap;

    long numKnot = g->getNumberVertices();
    int biggestColor = 0;
    int newColor;

    for (int i = 0; i < numKnot; i++)
    {
        //set of already used colors
        set<int> usedColorSet;

        for (int j = 0; j < i; j++)
        {
            //N := N U c(v(j))
            if (g->getEntry(j, i))
            { usedColorSet.insert(coloringMap.at(j)); }
        }

        newColor = getMinFreeColor(&usedColorSet, numKnot);

        //update biggest color metric
        if (newColor > biggestColor)
        { biggestColor = newColor; }

        //append new knot<->color mapping
        coloringMap.insert(pair<key_t, int>(i, newColor));
    }

    g->setColor(coloringMap);
    g->setNumColors(biggestColor);
}

//return the min unused color
int Algorithms::getMinFreeColor(set<int> *colorSet, long numKnots)
{
    //iterate through all possible colors and retrieve the smallest not yet mapped one
    for (int color = 0; color < numKnots; color++)
    {
        if (find(colorSet->begin(), colorSet->end(), color) == colorSet->end())
        { return color; }
    }

    return -1;
}

//return the number of triangles formed by vertices => matrix method
//num_triangles = 1/6 * trace(A^3)
long Algorithms::calcTriangles(int n, arma::Mat<short>* mat)
{
    arma::Mat<short> temp;
    temp = arma::Mat<short>(n, n);

#define MULTITHREAD
#ifdef MULTITHREAD
    //task is parallizable --> split lower triang matrix into 4 even parts

    int i1 = (int) (double) n / 2;
    int i2 = (int) (double) n / sqrt(2);
    int i3 = (int) (double) n * sqrt(3) / 2;

    //start threads
    thread  first(multWorker,  0, i1, &temp, mat);
    thread second(multWorker, i1, i2, &temp, mat);
    thread  third(multWorker, i2, i3, &temp, mat);
    thread fourth(multWorker, i3,  n, &temp, mat);

    //wait for threads to finish
    first.join();
    second.join();
    third.join();
    fourth.join();
#endif

#ifndef MULTITHREAD
    multWorker(0,n,&temp, &knotMat);
#endif

    //reflect lower triangluar matrix to full symmetric matrix
    temp = arma::symmatl(temp);

    //calculate trace(temp * A) = trace(A^3)
    int trace = 0;
    for(int i=0; i<n; i++)
    {
        trace += arma::dot(temp.row(i), mat->col(i));
    }

    return trace / 6;
}

//worker function for multithreaded matrix multiplication
void multWorker(int iStart, int iEnd, arma::Mat<short>* temp, arma::Mat<short>* knotMat)
{
    for(int i=iStart; i<iEnd; i++)
    {
        for(int j=0; j<=i; j++)
        { (*temp)(i,j) = arma::dot(knotMat->col(i), knotMat->col(j)); }
    }
}

//return the number of triangles formed by vertices => vector method
long Algorithms::calcTriangles2(int numKnot, vector<set<int>>* neighbours)
{
    long m_numTriangles = 0;

    //iterate through all vertices and find C(3)'s (triangles) in ascending order
    //to make sure we count every C(3) only once.
    //regard N(k3) with k3 being in N(k2) with k2 being in N(k1) an check if there is an edge from k3 back to k1
    for(int k1=0; k1<numKnot; k1++)
    {
        if ((*neighbours)[k1].size() < 2)
        { continue; }

        for (int k2 : (*neighbours)[k1])
        {
            if ((*neighbours)[k2].size() < 2 || k1 > k2)
            { continue; }

            for (int k3 : (*neighbours)[k2])
            {
                if ((*neighbours)[k3].size() < 2 || k2 > k3)
                { continue; }

                if (find((*neighbours)[k3].begin(), (*neighbours)[k3].end(), k1) != (*neighbours)[k3].end())
                { m_numTriangles++; }
            }
        }
    }

    return m_numTriangles;
}

//get number and size of connected components
pair<int, int> Algorithms::findConnectedComponents(int numKnot, vector<set<int>>* neighbours)
{
    unsigned int numberComponents = 0;
    unsigned int biggestComponent = 0;

    vector<bool> visited = vector<bool>(numKnot, false);
    vector<int> order;

    for(int i=0; i<numKnot; i++)
    {
        //skip if vertex visited already (component has already been counted)
        if(visited[i])
        { continue; }

        //start BFS with unvisited vertex -> unvisited component
        order = bfs(i, neighbours, visited);

        //update metrics
        numberComponents++;
        if(order.size() > biggestComponent)
        { biggestComponent = order.size(); }
    }

    return pair<int, int>(numberComponents, biggestComponent);
}

//execute the BFS algorithm on one connected component
vector<int> Algorithms::bfs(int start, vector<set<int>>* neighbours, vector<bool>& visited)
{
    int v;
    queue<int> Q;
    vector<int> travOrder;

    //add first vertex to queue and declare as known
    Q.push(start);
    visited[start] = true;
    travOrder.push_back(start);

    //main loop
    while(Q.size() != 0)
    {
        //retrieve the front most element of the queue
        v = Q.front();
        Q.pop();

        //further process all unknown neighbours of vertex v
        for(int w : (*neighbours)[v])
        {
            if(!visited[w])
            {
                Q.push(w);
                visited[w] = true;
                travOrder.push_back(w);
            }
        }
    }

    return travOrder;
}

//implementation of the single-source shortest-path dijkstra algorithm
float Algorithms::dijkstra(int from, int to, DirectedGraph* diGraph)
{
    unsigned int n;
    n = diGraph->getNumberVertices();

    vector<set<pair<int, float>>>* nbVec = diGraph->getNeighbourhood();

    //store the predecessors
    vector<int> pred(n, 0);

    //Q contains vertices with not yet known distances
    unsigned long sizeQ = n;
    bool Q[n] = { false };


    //vector containing the dist-values for every vertex
    vector<float> dist = vector<float>(n, FLOAT_INF);

    //initilaize start vertex with zero dist
    dist[from] = 0;

    //main loop
    while(sizeQ)
    {
        //debug
        //cout << "|Q| = " << sizeQ << endl;

        //find the vertex with min distance and remove it from Q
        int x = getMinDist(Q, n, dist);
        Q[x] = true;
        sizeQ--;

        //recalculate distances for every neighbour of x, which still is in Q
        updateDistances(nbVec, x, dist, Q, diGraph, &pred);
    }

    printPath(from, to, &pred);

    return dist[to];
}

//return the vertex in Q with minimal distance value
inline unsigned int Algorithms::getMinDist(bool Q[], unsigned int n, vector<float> &dist)
{
    unsigned int minVert;
    unsigned int minVal = -1;

    for(unsigned int k=0; k<n; k++)
    {
        //skip vertex if already removed from Q
        if(Q[k])
        { continue; }

        if(dist[k] < minVal)
        {
            minVal = dist[k];
            minVert = k;
        }
    }

    return minVert;
}

//recalculates the distances, in case there is a cheaper path over x now
inline void Algorithms::updateDistances(vector<set<pair<int, float>>>* nbVec, int x, vector<float>& dist, bool Q[], DirectedGraph* diGraph, vector<int>* pred)
{
    //iterate through neighbourhood of vertex x
    for(pair<int, float> entry : (*nbVec)[x])
    {
        int y = entry.first;

        //check if still in Q
        if(!Q[y])
        {
            //update if path over x is shorter than the previous shortest path
            if( dist[y] > dist[x] + diGraph->getEntry(x, y) )
            {
                dist[y] = dist[x] + diGraph->getEntry(x, y);
                (*pred)[y] = x;
            }
        }
    }
}

//print the shortest path from "from" to "to" determined by dijkstra
void Algorithms::printPath(int from, int to, vector<int>* pred)
{
    int curr = to;
    do
    {
        cout << curr << "<--";
        curr = pred->at(curr);
    }while(curr != from);
    cout << from << endl;
}

//calculate the weight of a MST
double Algorithms::getMSTWeightPrim(DirectedGraph *diGraph)
{
    unsigned long n = diGraph->getNumberVertices();

    priority_queue<int> Queue;
    for(unsigned int i=0; i<n; i++)
    { Queue.push(i); }

    set<int> spanningTree();
    vector<int> parentKnot = vector<int>(n, 0);

    return 0;
}

//calculate the weight of a MST
double Algorithms::getMSTWeightKruskal(DirectedGraph *diGraph)
{
    unsigned int numVerts = diGraph->getNumberVertices();
    unsigned int numEdges = diGraph->getNumberEdges() / 2;
    vector<edge> edges = diGraph->heapifyEdges();

    //edge part of MST or not
    bool inMST[numEdges] = {false};

    unsigned int edgesMST = 0;

    //holds the r number of every vertex
    int rNum[numVerts];
    for(unsigned int i=0; i<numVerts; i++)
    { rNum[i] = i; }

    //vertices in every r-component
    vector<set<int>> rComp(numVerts);

    //size of every r-component
    int rCompSize[numVerts];

    for(unsigned int i=0; i<numVerts; i++)
    {
        rComp[i].insert(i);
        rCompSize[i] = 1;
    }

    //iterate through all sorted edges of the graph
    //add them if doing so would not create a cycle
    unsigned int i=0;
    for(i=0; i<numEdges; i++)
    {
        int src = edges[i].from;
        int dst = edges[i].to;

        //skip if both vertices are of same r number
        if(rNum[src] == rNum[dst])
        { continue; }

        //add edge to MST otherwise
        inMST[i] = true;
        edgesMST++;

        //update r-numbers
        if(rCompSize[rNum[src]] >= rCompSize[rNum[dst]])
        {
            //set all vertex of CLASS[dst] to S[src]
            set<int> dstSet = rComp[rNum[dst]];
            for( int dstVert : dstSet )
            {
                //move dstVert to new component
                rComp[rNum[src]].insert(dstVert);
                rComp[rNum[dstVert]].erase(dstVert);
                rCompSize[rNum[src]]++;
                rCompSize[rNum[dstVert]]--;

                rNum[dstVert] = rNum[src];
            }
        }
        else
        {
            //set all vertex of CLASS[edges[i].form] to S[dst]
            set<int> srcSet = rComp[rNum[src]];
            for( int srcVert :  srcSet)
            {
                //move srcVert to new component
                rComp[rNum[dst]].insert(srcVert);
                rComp[rNum[srcVert]].erase(srcVert);
                rCompSize[rNum[dst]]++;
                rCompSize[rNum[srcVert]]--;

                rNum[srcVert] = rNum[dst];
            }
        }
    }

    //W = weight(MST)
    double W = 0;
    for(unsigned int i=0; i<numEdges; i++)
    {
        if(inMST[i])
        { W += edges[i].weight; }
    }

    if(edgesMST < numVerts-1)
    { cout << "more than one connected component!" << endl; }

    return W;
}

set<edge> Algorithms::GreedyMatching(Graph graph)
{

}
