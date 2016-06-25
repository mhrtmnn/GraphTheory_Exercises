//
// Created by marco on 6/25/16.
//

#ifndef GRAPHTHEORY_GIT_BACKPACK_HPP
#define GRAPHTHEORY_GIT_BACKPACK_HPP

#include <vector>
#include <bits/basic_string.h>
#include <string>

using namespace std;

class knapsackProblem
{
public:
    void parseFile(string s);

private:
    void addObject(int, int);

    int capacity;
    int currWeight;
    vector<pair<int, int>> objects;
    vector<bool> inKnapsack;

};


#endif //GRAPHTHEORY_GIT_BACKPACK_HPP
