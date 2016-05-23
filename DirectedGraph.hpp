//
// Created by marco on 5/10/16.
//

#ifndef GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP
#define GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP


#include <armadillo>
#include "BaseGraph.hpp"
using namespace std;

class DirectedGraph : public BaseGraph
{
public:
    void loadGraph(string p);

    float getEntry(int, int);
    arma::Mat<float>* getKnotMat();
    vector<set<pair<int, float >>>* getNeighbourhood();

    void print(arma::Mat<short>&);

private:
    arma::Mat<float> m_knotMat;
    vector<set<pair<int, float >>> m_neighbours;

    void parseLine(string, string, vector<pair<int, float>>*);
    void addVertices(vector<pair<int, float>> nb, int j);
    void initDataStructures(ifstream &fs);

    void print(arma::Mat<float>&);
};


#endif //GRAPHTHEORY_GIT_DIRECTEDGRAPH_HPP
