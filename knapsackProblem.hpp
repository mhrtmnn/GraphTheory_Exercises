//
// Created by marco on 6/25/16.
//

#ifndef GRAPHTHEORY_GIT_BACKPACK_HPP
#define GRAPHTHEORY_GIT_BACKPACK_HPP

#include <vector>
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
    int getCapacity();
    vector<struct object*> getObjects();


private:
    void addObject(int, int);

    int capacity;
    int currWeight;
    vector<struct object*> objects;
    vector<bool> inKnapsack;
};


#endif //GRAPHTHEORY_GIT_BACKPACK_HPP
