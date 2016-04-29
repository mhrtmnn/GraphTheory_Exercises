//
// Created by marco on 4/20/16.
//

#include "algorithms.hpp"


int algorithms::randomGreedy(Graph *g, int n)
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
            if (g->graphContainsEdge(j, k))
           { usedColorSet.insert(coloringMap.at(j)); }
        }

        newColor = getMinFreeColor(&usedColorSet, numKnot);
        if (newColor > biggestColor)
        { biggestColor = newColor; }

        coloringMap.insert(std::pair<key_t, int>(i, newColor));
    }
    return biggestColor;
}

void algorithms::GreedyColoring(Graph *g)
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
            if (g->graphContainsEdge(j, i))
            { usedColorSet.insert(coloringMap.at(j)); }
        }

        newColor = getMinFreeColor(&usedColorSet, numKnot);
        if (newColor > biggestColor)
        { biggestColor = newColor; }

        coloringMap.insert(std::pair<key_t, int>(i, newColor));
    }

    g->setColor(coloringMap);
    g->setNumColors(biggestColor);
}

int algorithms::getMinFreeColor(std::set<int> *colorSet, long numKnots)
{
    for (int color = 0; color < numKnots; color++)
    {
        if (std::find(colorSet->begin(), colorSet->end(), color) == colorSet->end())
        { return color; }
    }
    return -1;
}


//return the number of triangles formed by vertices
int algorithms::calcTriangles(Graph *g)
{
    int i = 0;
    int numVert = g->getNumberVertices();
    int m_numTriangles = 0;

    for(int i=0; i<numVert; i++)
    {
        if ( g->getDeg(i) < 2)
        { continue; }

        for (int j=0; j<numVert; j++)
        {
            if ( g->getDeg(i) < 2 || !(g->graphContainsEdge(i,j)) )
            { continue; }
            // TODO

        }
    }
    return m_numTriangles;
}
