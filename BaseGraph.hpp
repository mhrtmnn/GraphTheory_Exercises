//
// Created by marco on 5/9/16.
//

#ifndef GRAPHTHEORY_GIT_BASEGRAPH_HPP
#define GRAPHTHEORY_GIT_BASEGRAPH_HPP

#include <set>
#include <type_traits>
#include <fstream>
#include <vector>
#include <sstream>


class BaseGraph
{
public:
    BaseGraph();

    virtual void loadGraph(std::string p) = 0;

    long int getNumberVertices() const;
    long int getNumberEdges() const;

protected:
    int m_numKnots;
    int m_numEdges;

    virtual void initDataStructures(std::ifstream &) = 0;

    //parse one line of the text file --> templatze func must be in header
    template <typename T>
    void parseLine(std::string line, std::vector<T>* nb)
    {
        if (line.size() == 0)
        { return; }

        std::stringstream lineStream(line);
        std::string s;
        T item;
        bool isInt = std::is_same<T, int>::value;

        while(std::getline(lineStream, s, ','))
        {
            item = isInt ? std::stoi(s) : std::stof(s);
            nb->push_back(item);
        }
    }
};


#endif //GRAPHTHEORY_GIT_BASEGRAPH_HPP
