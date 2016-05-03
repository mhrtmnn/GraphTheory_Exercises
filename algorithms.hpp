//
// Created by marco on 4/20/16.
//

#ifndef GRAPHTHEORYEX1_ALGORITHMS_HPP
#define GRAPHTHEORYEX1_ALGORITHMS_HPP

#include <set>
#include <algorithm>

#include "Graph.hpp"

class algorithms
{
public:
    void GreedyColoring(Graph *g);
    int executeRandomGreedy(Graph *g, int n);
    int GreedyColoringCustom(Graph *, std::vector<int>*);

private:
    int getMinFreeColor(std::set<int> *, long);


};


#endif //GRAPHTHEORYEX1_ALGORITHMS_HPP
