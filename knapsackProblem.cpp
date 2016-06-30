//
// Created by marco on 6/25/16.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "knapsackProblem.hpp"

void knapsackProblem::parseFile(string s)
{
    ifstream fs;
    string line, token;
    int weight, value;

    fs.open(s);
    if (fs.is_open())
    {
        getline(fs, line);
        capacity = stoi(line);

        while (getline(fs, line))
        {
            stringstream lineStream(line);

            getline(lineStream, token, ',');
            value = stoi(token);
            getline(lineStream, token, ',');
            weight = stoi(token);

            addObject(value, weight);
        }
        cout << "loaded backpack" << endl;
     }
    else
    {
        cout << "load failed!" << endl;
        exit(-1);
    }
}

void knapsackProblem::addObject(int value, int weight)
{
    struct object* s = new struct object;
    s->value = value;
    s->weight = weight;
    objects.push_back(s);
}

int knapsackProblem::calcValue(vector<unsigned short> vec)
{
    int value = 0;
    for(auto i : vec)
    {
        value += objects[i-1]->value;
    }

    return value;
}

int knapsackProblem::calcValue(vector<int> vec)
{
    int value = 0;
    for(auto i : vec)
    {
        value += objects[i-1]->value;
    }

    return value;
}

int knapsackProblem::calcWeight(vector<unsigned short> vec)
{
    int weight = 0;
    for(auto i : vec)
    {
        weight += objects[i-1]->weight;
    }

    return weight;
}

int knapsackProblem::calcWeight(vector<int> vec)
{
    int weight = 0;
    for(auto i : vec)
    {
        weight += objects[i-1]->weight;
    }

    return weight;
}

int knapsackProblem::getCapacity()
{
    return capacity;
}

vector<struct object *> knapsackProblem::getObjects()
{
    return objects;
}
