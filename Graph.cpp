//
// Created by marco on 4/8/16.
//

#include "Graph.hpp"
#include "algorithms.hpp"
#include <algorithm>

//constructor
Graph::Graph() : m_numKnots(0), m_numEdges(0), m_maxDeg(0), m_numTriangles(-1), m_numIsolatedVertices(0), m_avgDeg(0)
{ }

void Graph::create(int size, int poss)
{

}


void Graph::initMatrix(std::ifstream &fs)
{
    int lines;
    std::string line;
    for (lines = 0; std::getline(fs, line); lines++);

    //last line contains "end"
    lines -= 1;
    m_numKnots = lines;

    for (int i = 0; i < lines; i++)
    { knotMatrix.push_back(std::vector<bool>((unsigned long) i + 1, false)); }
}

void Graph::addKnots(std::vector<int> neighbourVec, int k1)
{
    for (std::vector<int>::iterator iter = neighbourVec.begin(); iter != neighbourVec.end(); iter++)
    {
        int k2 = *iter - 1;
        if (k1 < k2)
        { knotMatrix[k2][k1] = true; }
        else
        { knotMatrix[k1][k2] = true; }
    }
}

int Graph::getDeg(int k)
{
    int deg = 0;
    int numVert = getNumberVertices();

    for(int j=0; j<numVert; j++)
    {
        if( graphContainsEdge(j, k) )
        { deg++; }
    }

    return deg;
}

//check whether or not edge is element graph
bool Graph::graphContainsEdge(int k1, int k2) const
{
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



void Graph::printColor() const
{
    std::cout << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "                COLORING                 " << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << std::endl;

    for (std::map<key_t, int>::const_iterator iter = m_coloring.begin(); iter != m_coloring.end(); iter++)
    { std::cout << iter->first + 1 << " has color: " << iter->second << std::endl; }

}

//return the number of knots with 0 neighbours
int Graph::getNumberIsolated() const
{ return m_numIsolatedVertices; }

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
double Graph::getAvgDeg() const
{ return m_avgDeg; }

//destructor
Graph::~Graph()
{ }
