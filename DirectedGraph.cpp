//
// Created by marco on 5/10/16.
//

#include "DirectedGraph.hpp"
using namespace std;


//read a graph from text file, create appropriate vertices and edges
void DirectedGraph::loadGraph(string p)
{
    ifstream fs;
    fs.open(p);

    int row = 0;
    string neighbourLine;
    string weightLine;

    if (fs.is_open())
    {
        initDataStructures(fs);
        fs.clear();
        fs.seekg(ios_base::beg);

        while (getline(fs, neighbourLine))
        {
            if (!neighbourLine.find("end"))
            { break; }

            getline(fs, weightLine);

            //get mapping of row's neighbouring vertices and their weights
            vector<pair<int, float>> nb;
            parseLine(neighbourLine, weightLine, &nb);

            addVertices(nb, row);

            m_numEdges += nb.size();
            row++;
        }
        cout << "\ngraph loaded\n";

        //debug
        //print(m_knotMat);
    }
}

void DirectedGraph::parseLine(string nl, string wl, vector<pair<int, float>>* nb)
{
    if (nl.size() == 0)
    { return; }

    stringstream nStream(nl);
    stringstream wStream(wl);

    string ns, ws;

    while(getline(nStream, ns, ','))
    {
        getline(wStream, ws, ',');

        nb->push_back(pair<int, float>(stoi(ns)-1, stof(ws)));
    }
}

void DirectedGraph::initDataStructures(ifstream &fs)
{
    int lines;
    string line;
    for (lines = 0; getline(fs, line); lines++)
        ;

    //last line contains "end" and two lines per vertex
    lines -= 1;
    lines /= 2;
    m_numKnots = lines;

    m_knotMat = arma::Mat<float>(lines, lines, arma::fill::zeros);
    m_neighbours = vector<set<pair<int, float>>>(lines, set<pair<int, float >>());
}

//add vertices to matrix --> file uses numbering 1,2,3... we use 0,1,2...
void DirectedGraph::addVertices(vector<pair<int, float>> nb, int j)
{
    //add entry to matrix and to neighbourhood vector
    for(pair<int, float> entry : nb)
    {
        m_knotMat(j, entry.first) = entry.second;
        m_neighbours[j].insert(entry);
    }
}

float DirectedGraph::getEntry(int k1, int k2)
{ return m_knotMat(k1, k2); }

//return the adj matrix
arma::Mat<float>* DirectedGraph::getKnotMat()
{ return &m_knotMat; }

//return the neighbourhood vector
vector<set<pair<int, float>>>* DirectedGraph::getNeighbourhood()
{ return &m_neighbours;}

void DirectedGraph::print(arma::Mat<float>& M)
{
    for(int i=0; i<m_numKnots; i++)
    {
        for(int j=0; j<m_numKnots; j++)
        { cout << M(i,j) << " "; }
        cout << endl;
    }
}

vector<edge> DirectedGraph::heapifyEdges()
{
    //undirected graph --> half the edges are duplicates
    std::vector<edge> edgeVec = std::vector<edge>(m_numEdges/2);

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
    std::sort(edgeVec.begin(), edgeVec.end(), [](edge a, edge b)->bool { return a.weight > b.weight;});

    return edgeVec;
};


