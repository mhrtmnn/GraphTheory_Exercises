//
// Created by marco on 6/25/16.
//

#ifndef GRAPHTHEORY_GIT_BACKPACK_HPP
#define GRAPHTHEORY_GIT_BACKPACK_HPP

#include <vector>
#include <bits/basic_string.h>
#include <string>

using namespace std;
struct object
{
    int value;
    int weight;
};

class knapsackProblem
{
public:
    void parseFile(string s);
    int calcValue(vector<unsigned short>);
    int calcWeight(vector<unsigned short>);
    vector<unsigned short> solveKP();
    int getCapacity();

private:
    void addObject(int, int);
    int min(int a, int b){ return a < b ? a : b; }

    int capacity;
    int currWeight;
    vector<struct object*> objects;
    vector<bool> inKnapsack;
};


#endif //GRAPHTHEORY_GIT_BACKPACK_HPP
