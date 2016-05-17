//
// Created by marco on 5/10/16.
//

#ifndef GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP
#define GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP


#include <armadillo>
#include "BaseGraph.hpp"

class DirectedGraph : public BaseGraph
{
public:
    void loadGraph(std::string p);

    float getEntry(int, int);
    arma::Mat<float>* getKnotMat();
    std::vector<std::set<std::pair<int, float >>>* getNeighbourhood();

    void print(arma::Mat<short>&);

private:
    arma::Mat<float> m_knotMat;
    std::vector<std::set<std::pair<int, float >>> m_neighbours;

    void parseLine(std::string, std::string, std::vector<std::pair<int, float>>*);
    void addVertices(std::vector<std::pair<int, float>> nb, int j);
    void initDataStructures(std::ifstream &fs);

    void print(arma::Mat<float>&);
};


#endif //GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP
