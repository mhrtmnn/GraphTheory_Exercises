//
// Created by marco on 6/18/16.
//

#include <cstdlib>
#include <stdlib.h>
#include "ComplexityAlgorithms.hpp"

bool ComplexityAlgorithms::randomWalk(satFormula *S, int t)
{
    for(int u=0; u<t; u++)
    {
        for(int i=0; i<S->n; i++)
        {
            if( rand() % 2 )
            {
                S->xVal[i] = true;
            }
        }

        for(int v=0; v<3*S->n; v++)
        {
            if(satisfied(S))
            { return true; }

            int i, l;
            //choose random: l from {l in [m] : (s(1,∨) V ... V s(l,k) ) not satisfied}
            l = chooseL(S);

            //choose random: i from { j in [n] : x(j) or x(j) in {s(1,∨) V ... V s(l,k)} }
            i = chooseI(S, l);

            //flip the value of the i-th variable xi
            S->xVal[i] = ~S->xVal[i];
        }
    }

    return false;
}

//check whether or not k-SAT formula with m clauses is satisfied or not
bool ComplexityAlgorithms::satisfied(struct satFormula *S) const
{
    for(int i=0, m=S->m; i<m; i++)
    {
        //the k-SAT formula is true iff all of its clauses evaluate to true
        if(!checkClause(S, i))
        { return false; }
    }

    return true;
}

//check whether or not the i-th Clause of the k-SAT formula evaluates to true
bool ComplexityAlgorithms::checkClause(struct satFormula *S, int i) const
{
    for(int j=0; j<S->k; j++)
    {
        //combine the sign of xi with its value
        //the whole clause is true iff one of the literals evaluates to true
        if(S->xData[i][j].second ^ S->xVal[ S->xData[i][j].first ])
        { return true; }
    }

    return false;
}

//randomly choose a clause which is not fulfilled
int ComplexityAlgorithms::chooseL(struct satFormula *S) const
{
    int l, m;
    m = S->m;

    do
    {
        l = rand() % m;

    }while(checkClause(S, l));

    return l;
}

//randomly choose an index, which is the index (name) of a literal in the not fulfilled clause
int ComplexityAlgorithms::chooseI(struct satFormula *S, int l) const
{
    int r = rand() % S->k;
    return S->xData[l][r].first;
}

vector<unsigned short> ComplexityAlgorithms::solveKP(knapsackProblem* kp)
{
    vector<struct object*> objects = kp->getObjects();
    int capacity = kp->getCapacity();
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
        unsigned short fi = (unsigned short) objects[i-1]->value;
        unsigned short gi = (unsigned short) objects[i-1]->weight;

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

unsigned short ComplexityAlgorithms::solveKP2(knapsackProblem *kp)
{
    vector<struct object*> objects = kp->getObjects();
    int C = kp->getCapacity();
    int n = (int) objects.size();

    auto **M = new unsigned short*[n+1];
    for(int i=0; i<n+1; i++)
    {
        M[i] = new unsigned short[C+1]{0};
    }

    for(int i=1; i<n+1; i++)
    {
        unsigned short v = (unsigned short) objects[i-1]->value;
        unsigned short w = (unsigned short) objects[i-1]->weight;

        for(int j=0; j<C+1; j++)
        {
            if( w > j )
            {
                M[i][j] = M[i-1][j];
            }
            else
            {
                M[i][j] = max(M[i-1][j], M[i-1][j-w] + v);
            }
        }
    }


    return M[n][C];
}
