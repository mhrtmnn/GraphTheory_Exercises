//
// Created by marco on 5/9/16.
//

#include "BaseGraph.hpp"

BaseGraph::BaseGraph() : m_numKnots(0), m_numEdges(0)
{}

void BaseGraph::initDataStructures(std::ifstream &fs, bool isDirected)
{
    int lines;
    std::string line;
    for (lines = 0; std::getline(fs, line); lines++);

    //last line contains "end"
    lines -= 1;
    isDirected ? m_numKnots = lines/2 : m_numKnots = lines;

    m_knotMat = arma::Mat<short>(lines, lines, arma::fill::zeros);
    m_neighbours = std::vector<std::set<int>>(lines, std::set<int>());
}

void BaseGraph::print(arma::Mat<short>& M)
{
    for(int i=0; i<m_numKnots; i++)
    {
        for(int j=0; j<m_numKnots; j++)
        { std::cout << M(i,j) << " "; }
        std::cout << std::endl;
    }
}

//return entry A(k1,k2)
int BaseGraph::getEntry(int k1, int k2)
{ return m_knotMat(k1, k2); }

//get number of knots
long int BaseGraph::getNumberVertices() const
{ return m_numKnots; }

//get number of edges
long int BaseGraph::getNumberEdges() const
{ return m_numEdges; }

//return the adj matrix
arma::Mat<short>* BaseGraph::getKnotMat()
{ return &m_knotMat; }

//return the neighbourhood vector
std::vector<std::set<int>>* BaseGraph::getNeighbourhood()
{ return &m_neighbours;}
