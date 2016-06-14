//
// Created by marco on 4/8/16.
//

#include "Graph.hpp"
using namespace std;


void multWorker(int iStart, int iEnd, arma::Mat<short>* temp, arma::Mat<short>* knotMat);

//constructor
Graph::Graph() : m_numIsolatedVertices(-1), m_numColors(-1), m_avgDeg(-1), m_maxDeg(0)
{}

//read a graph from text file, create appropriate vertices and edges
void Graph::loadGraph(string p)
{
    ifstream fs;
    fs.open(p);

    int row = 0;
    string line;
    if (fs.is_open())
    {
        initDataStructures(fs);
        fs.clear();
        fs.seekg(ios_base::beg);

        while (getline(fs, line))
        {
            if (!line.find("end"))
            { break; }

            vector<int> nb;
            parseLine(line, &nb);

            m_numEdges += nb.size();

            addVertices(nb, row);
            row++;
        }

        //reflect lower tri to quad tri
        m_knotMat = arma::symmatl(m_knotMat);

        //every edge counted twice
        m_numEdges /= 2;

        //debug
        //print(m_knotMat);
    }
    else
    {
        cout << "load failed!" << endl;
        exit(-1);
    }
}

void Graph::parseLine(string line, vector<int>* nb)
{
    if (line.size() == 0)
    { return; }

    stringstream lineStream(line);
    string s;

    while(getline(lineStream, s, ','))
    {
        nb->push_back(stoi(s));
    }
}

void Graph::initDataStructures(ifstream &fs)
{
    int lines;
    string line;
    for (lines = 0; getline(fs, line); lines++)
        ;

    //last line contains "end"
    lines -= 1;
    m_numKnots = lines;

    m_knotMat = arma::Mat<short>(lines, lines, arma::fill::zeros);
    m_neighbours = vector<set<int>>(lines, set<int>());
}

//add vertices to matrix --> file uses numbering 1,2,3... we use 0,1,2...
void Graph::addVertices(vector<int> nb, int j)
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
    m_neighbours = vector<set<int>>(n, set<int>());


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

//get avg degree
double Graph::getAvgDeg()
{
    if(m_avgDeg < 0)
    { m_avgDeg = calcAvgDeg(); }
    return m_avgDeg;
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
void Graph::setColor(map<int, int> colorMap)
{ m_coloring = colorMap; }

//set number of colors needed for coloring
void Graph::setNumColors(int c)
{ m_numColors = c; }

//return number of needed colors
int Graph::getNumberColors()
{ return m_numColors; }

//get the maximum number of edges of a single knot
long int Graph::getHighestDeg() const
{ return m_maxDeg; }

int Graph::getEntry(int k1, int k2)
{ return m_knotMat(k1, k2); }

//return the adj matrix
arma::Mat<short>* Graph::getKnotMat()
{ return &m_knotMat; }

//return the neighbourhood vector
vector<set<int>>* Graph::getNeighbourhood()
{ return &m_neighbours;}

void Graph::print(arma::Mat<short>& M)
{
    for(int i=0; i<m_numKnots; i++)
    {
        for(int j=0; j<m_numKnots; j++)
        { cout << M(i,j) << " "; }
        cout << endl;
    }
}

vector<edge> Graph::heapifyEdges()
{
    //undirected graph --> half the edges are duplicates
    std::vector<edge> edgeVec = std::vector<edge>(m_numEdges);

    int pos = 0;
    float weight;

    for(int i=0; i<m_numKnots; i++)
    {
        for(int j=0; j<i; j++)
        {
            if( (weight = getEntry(i, j)) != 0 )
            {
                edgeVec[pos++] = {i,j,weight};
            }
        }
    }

#ifdef FIND_MIN_MST
    std::sort(edgeVec.begin(), edgeVec.end(), [](edge a, edge b)->bool { return a.weight < b.weight;});
#endif
#ifndef FIND_MIN_MST
    std::sort(edgeVec.begin(), edgeVec.end(), [](edge a, edge b)->bool { return a.weight > b.weight;});
#endif

    return edgeVec;
};


//destructor
Graph::~Graph()
{ }
