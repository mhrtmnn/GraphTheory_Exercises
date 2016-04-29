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

class Graph
{
public:
    Graph();

    void create(int size, int poss);

    void print() const;

    void printIsolated() const;

    void printColor() const;

    long int getHighestDeg() const;

    long int getNumberVertices() const;

    int getDeg(int);

    long int getNumberEdges() const;

    int getNumberIsolated() const;

    void setColor(std::map<int, int>);

    void setNumColors(int);

    int getNumberColors();

    int getTriangles();

    double getAvgDeg() const;

    bool graphContainsEdge(int, int) const;

    virtual ~Graph();

private:
    void addKnots(std::vector<int>, int);

    void initMatrix(std::ifstream &);

    std::vector<std::vector<bool> > knotMatrix;

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
