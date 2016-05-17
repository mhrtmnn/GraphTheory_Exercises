//
// Created by marco on 5/10/16.
//

#include "DirectedGraph.hpp"


//read a graph from text file, create appropriate vertices and edges
void DirectedGraph::loadGraph(std::string p)
{
    std::ifstream fs;
    fs.open(p);

    int row = 0;
    std::string neighbourLine;
    std::string weightLine;

    if (fs.is_open())
    {
        initDataStructures(fs);
        fs.clear();
        fs.seekg(std::ios_base::beg);

        while (getline(fs, neighbourLine))
        {
            if (!neighbourLine.find("end"))
            { break; }

            getline(fs, weightLine);

            //get mapping of row's neighbouring vertices and their weights
            std::vector<std::pair<int, float>> nb;
            parseLine(neighbourLine, weightLine, &nb);

            addVertices(nb, row);

            m_numEdges += nb.size();
            row++;
        }
        std::cout << "\ngraph loaded\n";

        //every edge counted twice
        m_numEdges /= 2;

        //debug
        //print(m_knotMat);
    }
}

void DirectedGraph::parseLine(std::string nl, std::string wl, std::vector<std::pair<int, float>>* nb)
{
    if (nl.size() == 0)
    { return; }

    std::stringstream nStream(nl);
    std::stringstream wStream(wl);

    std::string ns, ws;

    while(std::getline(nStream, ns, ','))
    {
        std::getline(wStream, ws, ',');

        nb->push_back(std::pair<int, float>(std::stoi(ns)-1, std::stof(ws)));
    }
}

void DirectedGraph::initDataStructures(std::ifstream &fs)
{
    int lines;
    std::string line;
    for (lines = 0; std::getline(fs, line); lines++)
        ;

    //last line contains "end" and two lines per vertex
    lines -= 1;
    lines /= 2;
    m_numKnots = lines;

    m_knotMat = arma::Mat<float>(lines, lines, arma::fill::zeros);
    m_neighbours = std::vector<std::set<std::pair<int, float>>>(lines, std::set<std::pair<int, float >>());
}

//add vertices to matrix --> file uses numbering 1,2,3... we use 0,1,2...
void DirectedGraph::addVertices(std::vector<std::pair<int, float>> nb, int j)
{
    //add entry to matrix and to neighbourhood vector
    for(std::pair<int, float> entry : nb)
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
std::vector<std::set<std::pair<int, float>>>* DirectedGraph::getNeighbourhood()
{ return &m_neighbours;}

void DirectedGraph::print(arma::Mat<float>& M)
{
    for(int i=0; i<m_numKnots; i++)
    {
        for(int j=0; j<m_numKnots; j++)
        { std::cout << M(i,j) << " "; }
        std::cout << std::endl;
    }
}
