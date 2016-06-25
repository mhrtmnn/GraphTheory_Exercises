//
// Created by marco on 6/25/16.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "knapsackProblem.hpp"
#define INF -1

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
    s->val = value;
    s->weight = weight;
    objects.push_back(s);
}

int knapsackProblem::solveKP()
{
    int n = objects.size();
    int F = 0;
    for(auto p : objects)
    {
        F += p->val;
    }

    vector<int> I[n+1][F+1];

    int M[n+1][F+1]{0};
    for(int i=1; i<=F; i++)
    {
        M[0][i] = INF;
    }

    for(int i=1; i<=n; i++)
    {
        for(int k=0; k<=F; k++)
        {
            if((objects[i]->val < k))
            {
                if(M[i-1][k-objects[i]->val]+objects[i]->weight < ((capacity < M[i-1][k-objects[i]->val]) ? (capacity) : (M[i-1][k-objects[i]->val])))
                {
                    M[i][k] = M[i-1][k-objects[i]->val] + objects[i]->weight;
                    I[i][k] = I[i-1][k-objects[i]->val];
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



    return 0;
}
