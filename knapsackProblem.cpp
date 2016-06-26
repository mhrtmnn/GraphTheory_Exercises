//
// Created by marco on 6/25/16.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include "knapsackProblem.hpp"
#define INF std::numeric_limits<unsigned short>::max()

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

vector<unsigned short> knapsackProblem::solveKP()
{
    int n = objects.size();
    int F = 0;
    for(auto p : objects)
    {
        F += p->value;
    }

    auto **I = new vector<unsigned short>*[n+1];
    auto **M = new unsigned short*[n+1];
    for(int i=0; i<n+1; i++)
    {
        I[i] = new vector<unsigned short>[F+1];
        M[i] = new unsigned short[F+1]{0};
    }

    for(int i=1; i<=F; i++)
    {
        M[0][i] = INF;
    }

    for(int i=1; i<n+1; i++)
    {
        unsigned short fi = objects[i-1]->value;
        unsigned short gi = objects[i-1]->weight;

        for(int k=0; k<F+1; k++)
        {
            if(fi <= k)
            {
                if(M[i-1][k-fi] + gi <= min(capacity, M[i-1][k]))
                {
                    M[i][k] = M[i-1][k-fi] + gi;
                    I[i][k] = I[i-1][k-fi];
                    I[i][k].push_back( i );
                }
                else
                {
                    M[i][k] = M[i-1][k];
                    I[i][k] = I[i-1][k];
                }
            }
        }
    }

    int k = 0;
    for(int i=0; i<F+1; i++)
    {
        if( M[n][i] > k && M[n][i] != INF )
        {
            k = i;
        }
    }
    auto vec = I[n][k];

    for(int i=0; i<=n; i++)
    {
        delete[] I[i];
        delete[] M[i];
    }

    return vec;
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
