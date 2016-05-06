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


class Graph
{
public:
    Graph();

    void loadGraph(std::string p);
    void randomCreate(int n, double p);
    long int getHighestDeg() const;
    long int getNumberVertices() const;
    long int getNumberEdges() const;
    int getNumberIsolated();
    void setColor(std::map<int, int>);
    void setNumColors(int);
    int getNumberColors();
    int getTriangles();
    double getAvgDeg();
    int getEntry(int, int);

    virtual ~Graph();

private:

    arma::Mat<int> m_knotMat;

    std::map<int, int> m_coloring;
    std::vector<std::set<int>> m_neighbours;

    int m_numEdges;
    int m_numKnots;
    int m_numTriangles;
    int m_numIsolatedVertices;
    int m_numColors;
    float m_avgDeg;
    unsigned long int m_maxDeg;

    void print(arma::Mat<int>&);
    void addVertices(std::vector<int> nb, int j);
    void initDataStructures(std::ifstream &fs);
    int getDeg(int);
    double calcAvgDeg();
    double calcTriangles();
    std::vector<int> parseLine(std::string line);

    algorithms alg;
};


#endif //GRAPHTHEORYEX1_GRAPH_HPP
