//
// Created by marco on 4/8/16.
//

#include "Graph.hpp"

void multWorker(int iStart, int iEnd, arma::Mat<short>* temp, arma::Mat<short>* knotMat);

//constructor
Graph::Graph() : m_numIsolatedVertices(-1), m_numColors(-1), m_avgDeg(-1), m_maxDeg(0)
{}

//read a graph from text file, create appropriate vertices and edges
void Graph::loadGraph(std::string p)
{
    std::ifstream fs;
    fs.open(p);

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
            parseLine(line, &nb);
            m_numEdges += nb.size();

            addVertices(nb, row);
            row++;
        }

        //reflect lower tri to quad tri
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
void Graph::parseLine(std::string line, std::vector<int>* nb)
{

    if (line.size() == 0)
    { return; }

    std::stringstream lineStream(line);
    std::string s;
    while(std::getline(lineStream, s, ','))
    {
        nb->push_back(std::stoi(s));
    }
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

//randomly create a new graph with randomly distributed edges
void Graph::randomCreate(int n, double p)
{
    m_numKnots = n;
    m_knotMat = arma::Mat<short>(n, n, arma::fill::zeros);
    m_neighbours = std::vector<std::set<int>>(n, std::set<int>());


    for(int i=1; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            if((rand() % n) < p * n)
            {
                m_knotMat(i,j) = 1;

                m_neighbours[j].insert(i);
                m_neighbours[i].insert(j);

                m_numEdges++;
            }
        }
    }

    //reflect lower triangular matrix to symmetric quadratic matrix
    m_knotMat = arma::symmatl(m_knotMat);
    //print(m_knotMat);
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

//get the maximum number of edges of a single knot
long int Graph::getHighestDeg() const
{ return m_maxDeg; }


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
