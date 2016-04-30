//
// Created by marco on 4/8/16.
//

#include "Graph.hpp"
#include "algorithms.hpp"
#include <algorithm>
#include <random>

//constructor
Graph::Graph() : m_numKnots(0), m_numEdges(0), m_maxDeg(0), m_numTriangles(-1), m_numIsolatedVertices(-1), m_avgDeg(-1)
{ }

void Graph::create(int n, double p)
{
    m_numKnots = n;
    std::random_device rd;
    for(int i=0; i<n; i++)
    {
        std::vector<bool> vec(i, false);

        for(int j=0; j<=i; j++)
        {
            if ((rd() % n) <= p * (n-1))
            {
                vec[j] = true;
                m_numEdges++;
            }
        }

        knotMatrix.push_back(vec);
    }
}

//calculate the degree of a given vertex
int Graph::getDeg(int k)
{
    int deg = 0;

    for(int j=0; j<m_numKnots; j++)
    {
        if( graphContainsEdge(j, k) )
        { deg++; }
    }
    return deg;
}

//calculate the average degree over all vertices
double Graph::calcAvgDeg()
{
    double deg = 0;
    for(int k=0; k<m_numKnots; k++)
    {
        deg += getDeg(k);
    }
    return deg / (double) m_numKnots;
}


//check whether or not edge is element graph
bool Graph::graphContainsEdge(int k1, int k2) const
{
    if(k1 == k2)
    { return false; }
    if (k1 < k2)
    { return knotMatrix[k2][k1]; }
    else
    { return knotMatrix[k1][k2]; }
}

void Graph::setColor(std::map<int, int> colorMap)
{ m_coloring = colorMap; }

void Graph::setNumColors(int c)
{ m_numColors = c; }

int Graph::getNumberColors()
{ return m_numColors; }

//return the number of knots with 0 neighbours
int Graph::getNumberIsolated()
{
    if(m_numIsolatedVertices < 0)
    {
        m_numIsolatedVertices = 0;
        for(int i=0; i<m_numKnots; i++)
        {
            if(!getDeg(i))
            {m_numIsolatedVertices++;}
        }
    }
    return m_numIsolatedVertices;
}

//return the number of triangles formed by vertices
int Graph::getTriangles()
{
    if(m_numTriangles<0)
    {
        algorithms alg;
        m_numTriangles = alg.calcTriangles(this);
    }
    return m_numTriangles;
}

//get the maximum number of edges of a single knot
long int Graph::getHighestDeg() const
{ return m_maxDeg; }

//get number of knots
long int Graph::getNumberVertices() const
{ return m_numKnots; }

//get number of edges
long int Graph::getNumberEdges() const
{ return m_numEdges; }

//get avg degree
double Graph::getAvgDeg()
{
    if(m_avgDeg < 0)
    {
        m_avgDeg = calcAvgDeg();
    }
    return m_avgDeg;
}

//destructor
Graph::~Graph()
{ }
