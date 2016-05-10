//
// Created by marco on 5/10/16.
//

#ifndef GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP
#define GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP


#include "BaseGraph.hpp"

class DirectedGraph : public BaseGraph
{
protected:
    void loadGraph(std::string p);

    void addVertices(std::vector<int> nb, int j);

};


#endif //GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP
