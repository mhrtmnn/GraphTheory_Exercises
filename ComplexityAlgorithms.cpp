//
// Created by marco on 6/18/16.
//

#include <cstdlib>
#include "ComplexityAlgorithms.hpp"

bool ComplexityAlgorithms::randomWalk(satFormular S, int t)
{
    for(int u=0; u<t; u++)
    {
        for(int i=0; i<S.n; i++)
        {
            if( rand() % 2 )
            {
                S.xVal[i] = true;
            }
        }

        for(int v=0; v<3*S.n; v++)
        {
            if(satisfiable(&S, 0, 0))
            {
                return true;
            }

            int i, l;
            //choose random: l from {l in [m] : (s(1,∨) V ... V s(l,k) ) not satisfied}
            //choose random: i from { j in [n] : x(j) or x(j) in {s(1,∨) V ... V s(l,k)} }
            //TODO

            //flip the value of the i-th variable xi
            S.xVal[i] = ~S.xVal[i];
        }
    }


}

//check whether or not k-SAT formula with m clauses is satisfiable or not
bool ComplexityAlgorithms::satisfiable(struct satFormular *S, int m, int k)
{
    for(int i=0; i<m; i++)
    {
        //the k-SAT formula is true iff all of its clauses evaluate to true
        if(!checkClausel(S, i, k))
        { return false; }
    }

    return true;
}

//check whether or not the i-th Clause of the k-SAT formula evaluates to true
bool ComplexityAlgorithms::checkClausel(struct satFormular *S, int i, int k)
{
    for(int j=0; j<k; j++)
    {
        //combine the sign of xi with its value
        //the whole clause is true iff one of the literals evaluates to true
        if(S->xSign[i][j] ^ S->xVal[i])
        { return true; }
    }

    return false;
}
