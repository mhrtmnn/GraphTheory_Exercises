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
    int val;
    int weight;
};

class knapsackProblem
{
public:
    void parseFile(string s);
    vector<unsigned short> solveKP();

private:
    void addObject(int, int);

    int capacity;
    int currWeight;
    vector<struct object*> objects;
    vector<bool> inKnapsack;
    int min(int a, int b){ return a < b ? a : b; }


};


#endif //GRAPHTHEORY_GIT_BACKPACK_HPP
