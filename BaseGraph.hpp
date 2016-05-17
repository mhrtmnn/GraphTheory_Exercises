//
// Created by marco on 5/9/16.
//

#ifndef GRAPHTHEORY_GIT_BASEGRAPH_HPP
#define GRAPHTHEORY_GIT_BASEGRAPH_HPP

#include <set>
#include <type_traits>
#include <fstream>
#include <vector>
#include <sstream>


class BaseGraph
{
public:
    BaseGraph();

    virtual void loadGraph(std::string p) = 0;

    long int getNumberVertices() const;
    long int getNumberEdges() const;

protected:
    int m_numKnots;
    int m_numEdges;

    virtual void initDataStructures(std::ifstream &) = 0;
};


#endif //GRAPHTHEORY_GIT_BASEGRAPH_HPP
