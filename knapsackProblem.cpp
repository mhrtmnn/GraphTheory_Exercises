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
    objects.push_back(pair<int, int>{value, weight});
}
