//
// Created by marco on 5/10/16.
//

#include "DirectedGraph.hpp"


//read a graph from text file, create appropriate vertices and edges
void DirectedGraph::loadGraph(std::string p)
{



}



void DirectedGraph::initDataStructures(std::ifstream &fs)
{
    int lines;
    std::string line;
    for (lines = 0; std::getline(fs, line); lines++);

    //last line contains "end"
    lines -= 1;

    m_knotMat = arma::Mat<float >(lines, lines, arma::fill::zeros);
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
