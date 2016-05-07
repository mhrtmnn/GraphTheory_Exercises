//
// Created by marco on 4/20/16.
//

#ifndef GRAPHTHEORYEX1_ALGORITHMS_HPP
#define GRAPHTHEORYEX1_ALGORITHMS_HPP

#include <set>
#include <queue>
#include <algorithm>
#include <armadillo>

#include "Graph.hpp"

class algorithms
{
public:
    void GreedyColoring(Graph *g);
    int executeRandomGreedy(Graph *g, int n);
    long calcTriangles(int, arma::Mat<short>*);
    long calcTriangles2(int numKnot, std::vector<std::set<int>>* neighbours);
    std::pair<int, int> findConnectedComponents(int, std::vector<std::set<int>>*);

private:
    int getMinFreeColor(std::set<int> *, long);
    int GreedyColoringCustom(Graph *, std::vector<int>*);
    std::vector<int> bfs(int, int, std::vector<std::set<int>>*);
};


#endif //GRAPHTHEORYEX1_ALGORITHMS_HPP
