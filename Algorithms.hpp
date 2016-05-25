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
#include "DirectedGraph.hpp"
using namespace std;

class Algorithms
{
public:
    void GreedyColoring(Graph *g);
    int executeRandomGreedy(Graph *g, int n);
    long calcTriangles(int, arma::Mat<short>*);
    long calcTriangles2(int numKnot, vector<set<int>>* neighbours);
    pair<int, int> findConnectedComponents(int, vector<set<int>>*);
    float dijkstra(int, int, DirectedGraph*);
    inline unsigned int getMinDist(bool [], unsigned int, vector<float> &);
    void updateDistances(vector<set<pair<int, float>>>*, int, vector<float>&, bool[], DirectedGraph*, vector<int>*);
    double getMSTWeight(DirectedGraph* diGraph);


private:
    int getMinFreeColor(set<int> *, long);
    int GreedyColoringCustom(Graph *, vector<int>*);
    vector<int> bfs(int, vector<set<int>>*, vector<bool>&);
    void printPath(int, int, vector<int>*);

};


#endif //GRAPHTHEORYEX1_ALGORITHMS_HPP
