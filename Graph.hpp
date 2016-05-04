//
// Created by marco on 4/8/16.
//

#ifndef GRAPHTHEORYEX1_GRAPH_HPP
#define GRAPHTHEORYEX1_GRAPH_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

#include <armadillo>


class Graph
{
public:
    Graph();

    void initMatrix(std::ifstream &fs);

    std::vector<int> parseLine(std::string line);

    void loadGraph(std::string p);

    void addVertices(std::vector<int> nb, int j);

    void randomCreate(int n, double p);

    long int getHighestDeg() const;

    long int getNumberVertices() const;

    int getDeg(int);

    long int getNumberEdges() const;

    int getNumberIsolated();

    void setColor(std::map<int, int>);

    void setNumColors(int);

    int getNumberColors();

    int getTriangles();

    double calcTriangles();

    double getAvgDeg();

    double calcAvgDeg();

    int getEntry(int, int);

    virtual ~Graph();

private:
    arma::Mat<int> knotMat;
    void print(arma::Mat<int>&);

    int m_numEdges;
    int m_numKnots;
    int m_numTriangles;
    int m_numIsolatedVertices;
    float m_avgDeg;
    int m_numColors;
    std::map<int, int> m_coloring;
    unsigned long int m_maxDeg;
};


#endif //GRAPHTHEORYEX1_GRAPH_HPP
