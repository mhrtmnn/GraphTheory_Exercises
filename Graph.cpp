//
// Created by marco on 4/8/16.
//

#include "Graph.hpp"

void multWorker(int iStart, int iEnd, arma::Mat<int>* temp, arma::Mat<int>* knotMat);

//constructor
Graph::Graph() : m_numKnots(0), m_numEdges(0), m_maxDeg(0), m_numTriangles(-1), m_numIsolatedVertices(-1), m_avgDeg(-1)
{
    alg = algorithms();
}

//read a graph from text file, create appropriate vertices and edges
void Graph::loadGraph(std::string p)
{
    std::ifstream fs;
    fs.open(p.c_str());

    int row = 0;
    std::string line;
    if (fs.is_open())
    {
        initDataStructures(fs);
        fs.clear();
        fs.seekg(std::ios_base::beg);

        while (getline(fs, line))
        {
            if (!line.find("end"))
            { break; }

            std::vector<int> nb;
            nb = parseLine(line);
            m_numEdges += nb.size();

            addVertices(nb, row);
            row++;
        }

        //refelct lower tri to quad tri
        m_knotMat = arma::symmatl(m_knotMat);

        //every edge counted twice
        m_numEdges /= 2;
    }
    else
    {
        std::cout << "load failed!" << std::endl;
        exit(-1);
    }
}

//parse one line of the text file
std::vector<int> Graph::parseLine(std::string line)
{
    std::vector<int> nb;

    if (line.size() == 0)
    { return nb; }

    std::string num = "";
    char c;

    for (unsigned int i = 0; i < line.length(); i++)
    {
        if ((c = line[i]) == ',')
        {
            nb.push_back(stoi(num));
            num = "";
        }
        else
        { num.push_back(c); }
    }
    nb.push_back(std::stoi(num));
    return nb;
}

//add vertices to matrix --> file uses numbering 1,2,3... we use 0,1,2...
void Graph::addVertices(std::vector<int> nb, int j)
{
    //add entry to lower triangular matrix and to neighbourhood vector
    for(int i : nb)
    {
        (i-1) < j ? m_knotMat(j, i-1) = 1 : m_knotMat(i-1, j) = 1;
        m_neighbours[j].insert(i-1);
    }
}

void Graph::initDataStructures(std::ifstream &fs)
{
    int lines;
    std::string line;
    for (lines = 0; std::getline(fs, line); lines++);

    //last line contains "end"
    lines -= 1;
    m_numKnots = lines;

    m_knotMat = arma::Mat<int>(lines, lines, arma::fill::eye);
    m_neighbours = std::vector<std::set<int>>(lines, std::set<int>());
    //print(knotMat);
}

//randomly create a new graph with randomly distributed edges
void Graph::randomCreate(int n, double p)
{
    m_numKnots = n;
    m_knotMat = arma::Mat<int>(n, n, arma::fill::eye);

    for(int i=1; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            if((rand() % n) < p * n)
            {
                m_knotMat(i,j) = 1;
                m_numEdges++;
            }
        }
    }
    //refelct lower triangular matrix to symmetric quadratic matrix
    m_knotMat = arma::symmatl(m_knotMat);
    //print(knotMat);
}

void Graph::print(arma::Mat<int>& M)
{
    for(int i=0; i<m_numKnots; i++)
    {
        for(int j=0; j<m_numKnots; j++)
        { std::cout << M(i,j) << " "; }
        std::cout << std::endl;
    }
}

//calculate the degree of a given vertex
int Graph::getDeg(int k)
{
    int deg = 0;

    for(int j=0; j<m_numKnots; j++)
    {
        if( m_knotMat(j, k) )
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

//return entry A(k1,k2)
int Graph::getEntry(int k1, int k2)
{ return m_knotMat(k1, k2); }

//set map with vertex : color mapping
void Graph::setColor(std::map<int, int> colorMap)
{ m_coloring = colorMap; }

//set number of colors needed for coloring
void Graph::setNumColors(int c)
{ m_numColors = c; }

//return number of needed colors
int Graph::getNumberColors()
{ return m_numColors; }

//return the number of knots with zero neighbours
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
    { m_numTriangles = calcTriangles(); }
    return m_numTriangles;
}

//calc the number of triangles in the graph
//num_triangles = 1/6 * trace(A^3)
double Graph::calcTriangles()
{
    double n = m_numKnots;
    arma::Mat<int> temp;
    temp = arma::Mat<int>(m_numKnots, m_numKnots);

#define MULTITHREAD
#ifdef MULTITHREAD
    //task is parallizable --> split lower triang matrix into 4 even parts
    double d1 = n / 2;
    double d2 =  n / sqrt(2);
    double d3 = n * sqrt(3) / 2;

    int i1 = (int) d1;
    int i2 = (int) d2;
    int i3 = (int) d3;

    //start threads
    std::thread  first(multWorker,  0, i1, &temp, &knotMat);
    std::thread second(multWorker, i1, i2, &temp, &knotMat);
    std::thread  third(multWorker, i2, i3, &temp, &knotMat);
    std::thread fourth(multWorker, i3, n,  &temp, &knotMat);

    //wait for threads to finish
    first.join();
    second.join();
    third.join();
    fourth.join();
#endif

#ifndef MULTITHREAD
    multWorker(0,n,&temp, &knotMat);
#endif

    temp = arma::symmatl(temp);

    int trace = 0;
    for(int i=0; i<n; i++)
    { trace += arma::dot(temp.row(i), knotMat.col(i)); }

    return trace / 6;
}

void multWorker(int iStart, int iEnd, arma::Mat<int>* temp, arma::Mat<int>* knotMat)
{
    for(int i=iStart; i<iEnd; i++)
    {
        for(int j=0; j<=i; j++)
        { (*temp)(i,j) = arma::dot(knotMat->col(i), knotMat->col(j)); }
    }
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
    { m_avgDeg = calcAvgDeg(); }
    return m_avgDeg;
}

//destructor
Graph::~Graph()
{ }
