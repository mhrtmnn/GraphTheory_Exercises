//
// Created by marco on 4/8/16.
//

#include "Graph.hpp"

//constructor
Graph::Graph() : m_numKnots(0), m_numEdges(0), m_maxDeg(0), m_numTriangles(-1), m_numIsolatedVertices(-1), m_avgDeg(-1)
{ }

//create a new graph with randomly distributed edges
void Graph::create(int n, double p)
{
    m_numKnots = n;
    std::random_device rd;
    knotMat = arma::Mat<int>(n,n,arma::fill::zeros);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(j==i)
            {
                continue;
            }
            else if((rd() % n) <= p * (n-1))
            {
                knotMat.at(i,j) = 1;
                knotMat.at(j,i) = 1;
                m_numEdges++;
            }
        }
    }
}

//calculate the degree of a given vertex
int Graph::getDeg(int k)
{
    int deg = 0;

    for(int j=0; j<m_numKnots; j++)
    {
        if( knotMat.at(j, k) )
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


int Graph::getEntry(int k1, int k2) const
{
    return knotMat.at(k1, k2);

// DEBUG
//    int a[5][5] = {{1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7},{4,5,6,7,8},{5,6,7,8,9}};
//    return a[k1][k2];

}


//set map with vertex : color mapping
void Graph::setColor(std::map<int, int> colorMap)
{ m_coloring = colorMap; }

//set number of colors needed for coloring
void Graph::setNumColors(int c)
{ m_numColors = c; }

//return number of needed colors
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
        m_numTriangles = calcTriangles();
    }
    return m_numTriangles;
}

//calc the number of triangles in the graph
//num_triangles = 1/6 * trace(A^3)
double Graph::calcTriangles()
{
    arma::Mat<int> A = arma::pow(knotMat, 3);

    double trace = arma::trace(A);
    return trace / 6;
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
