//
// Created by marco on 4/8/16.
//

#ifndef GRAPHTHEORYEX1_GRAPH_HPP
#define GRAPHTHEORYEX1_GRAPH_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <random>
#include <thread>

#define ARMA_NO_DEBUG
#include <armadillo>
#include "BaseGraph.hpp"
using namespace std;



class Graph : public BaseGraph
{
public:
    Graph();

    void loadGraph(string p);
    void randomCreate(int n, double p);

    long int getHighestDeg() const;
    double getAvgDeg();
    int getNumberIsolated();

    void setColor(map<int, int>);
    void setNumColors(int);
    int getNumberColors();

    int getEntry(int, int);
    arma::Mat<short>* getKnotMat();
    vector<set<int>>* getNeighbourhood();
    vector<edge> heapifyEdges();
    vector<edge> getAscEdges();

    void print(arma::Mat<short>&);

    virtual ~Graph();

private:
    void addVertices(vector<int> nb, int j);
    void initDataStructures(ifstream &fs);
    void parseLine(string line, vector<int>* nb);

    arma::Mat<short> m_knotMat;
    vector<set<int>> m_neighbours;
    map<int, int> m_coloring;
    int m_numIsolatedVertices;
    int m_numColors;
    float m_avgDeg;
    unsigned long int m_maxDeg;

    double calcAvgDeg();
    int getDeg(int);
};


#endif //GRAPHTHEORYEX1_GRAPH_HPP
