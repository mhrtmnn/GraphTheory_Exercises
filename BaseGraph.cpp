//
// Created by marco on 5/9/16.
//

#include <iostream>
#include "BaseGraph.hpp"

BaseGraph::BaseGraph() : m_numKnots(0), m_numEdges(0)
{}

//get number of knots
unsigned long int BaseGraph::getNumberVertices() const
{ return m_numKnots; }

//get number of edges
unsigned long int BaseGraph::getNumberEdges() const
{ return m_numEdges; }
