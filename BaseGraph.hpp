//
// Created by marco on 5/9/16.
//

#ifndef GRAPHTHEORY_GIT_BASEGRAPH_HPP
#define GRAPHTHEORY_GIT_BASEGRAPH_HPP

#define ARMA_NO_DEBUG
#include <armadillo>
#include <set>


class BaseGraph
{
public:
    BaseGraph();

    virtual void loadGraph(std::string p) = 0;

    long int getNumberVertices() const;
    long int getNumberEdges() const;
    int getEntry(int, int);

    arma::Mat<short>* getKnotMat();
    void print(arma::Mat<short>&);
    std::vector<std::set<int>>* getNeighbourhood();

protected:
    arma::Mat<short> m_knotMat;
    std::vector<std::set<int>> m_neighbours;

    int m_numKnots;
    int m_numEdges;

    virtual void initDataStructures(std::ifstream &fs);
    virtual void addVertices(std::vector<int> nb, int j) = 0;
    virtual void parseLine(std::string, std::vector<int>*) = 0;




};


#endif //GRAPHTHEORY_GIT_BASEGRAPH_HPP
