//
// Created by marco on 4/20/16.
//

#include "algorithms.hpp"

//PROTOTYPES
void multWorker(int, int, arma::Mat<short>*, arma::Mat<short>*);

//apply greedy alg to n randomly selected knot orders
int algorithms::executeRandomGreedy(Graph *g, int n)
{
    //run greedy with randomly selected knot orders
    std::vector<int> num = std::vector<int>(g->getNumberVertices());
    std::iota(num.begin(), num.end(), 0);
    int minColor = 1000;
    int currColor;
    for(int i=0; i<n; i++)
    {
        currColor = GreedyColoringCustom(g, &num);
        std::random_shuffle ( num.begin(), num.end() );

        std::cout << currColor << "|" ;
        if(currColor<minColor)
        { minColor = currColor; }
    }

    return minColor;
}

//implementation of the greedy coloring alg: colors vertices in a custom order
int algorithms::GreedyColoringCustom(Graph *g, std::vector<int> *custOrder)
{
    //map holding the knot<->color mapping
    std::map<int, int> coloringMap;

    long numKnot = g->getNumberVertices();
    int biggestColor = 0;
    int newColor;

    for (int i = 0; i < numKnot; i++)
    {
        int k = (*custOrder)[i];

        //set of already used colors
        std::set<int> usedColorSet;

        for (int j = 0; j < i; j++)
        {
            //N := N U c(v(j))
            if (g->getEntry(j, k))
            { usedColorSet.insert(coloringMap.at(j)); }
        }

        newColor = getMinFreeColor(&usedColorSet, numKnot);
        if (newColor > biggestColor)
        { biggestColor = newColor; }

        coloringMap.insert(std::pair<key_t, int>(i, newColor));
    }

    return biggestColor;
}

//implementation of the greedy coloring alg: colors vertices in ascending order
void algorithms::GreedyColoring(Graph* g)
{
    //map holding the knot<->color mapping
    std::map<int, int> coloringMap;

    long numKnot = g->getNumberVertices();
    int biggestColor = 0;
    int newColor;

    for (int i = 0; i < numKnot; i++)
    {
        //set of already used colors
        std::set<int> usedColorSet;

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
        coloringMap.insert(std::pair<key_t, int>(i, newColor));
    }

    g->setColor(coloringMap);
    g->setNumColors(biggestColor);
}

//return the min unused color
int algorithms::getMinFreeColor(std::set<int> *colorSet, long numKnots)
{
    //iterate through all possible colors and retrieve the smallest not yet mapped one
    for (int color = 0; color < numKnots; color++)
    {
        if (std::find(colorSet->begin(), colorSet->end(), color) == colorSet->end())
        { return color; }
    }

    return -1;
}

//return the number of triangles formed by vertices => matrix method
//num_triangles = 1/6 * trace(A^3)
long algorithms::calcTriangles(int n, arma::Mat<short>* mat)
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
    std::thread  first(multWorker,  0, i1, &temp, mat);
    std::thread second(multWorker, i1, i2, &temp, mat);
    std::thread  third(multWorker, i2, i3, &temp, mat);
    std::thread fourth(multWorker, i3,  n, &temp, mat);

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
long algorithms::calcTriangles2(int numKnot, std::vector<std::set<int>>* neighbours)
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

                if (std::find((*neighbours)[k3].begin(), (*neighbours)[k3].end(), k1) != (*neighbours)[k3].end())
                { m_numTriangles++; }
            }
        }
    }

    return m_numTriangles;
}

//get number and size of connected components
std::pair<int, int> algorithms::findConnectedComponents(int numKnot, std::vector<std::set<int>>* neighbours)
{
    unsigned int numberComponents = 0;
    unsigned int biggestComponent = 0;

    std::vector<bool> visited = std::vector<bool>(numKnot, false);
    std::vector<int> order;

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

    return std::pair<int, int>(numberComponents, biggestComponent);
}

//execute the BFS algorithm on one connected component
std::vector<int> algorithms::bfs(int start, std::vector<std::set<int>>* neighbours, std::vector<bool>& visited)
{
    int v;
    std::queue<int> Q;
    std::vector<int> travOrder;

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
