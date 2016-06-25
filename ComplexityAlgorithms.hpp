//
// Created by marco on 6/18/16.
//

#ifndef GRAPHTHEORY_GIT_COMPLEXITYALGORITHMS_HPP
#define GRAPHTHEORY_GIT_COMPLEXITYALGORITHMS_HPP

#include <vector>

using namespace std;

struct satFormula
{
    int k;                                  //k sat formula
    int m;                                  //m clauses per formula
    int n;                                  //x1,...,xn available per clause
    vector<vector<pair<int, bool>>> xData;  //number and sign of literals
    bool *xVal;                             //truth value of xi
};


class ComplexityAlgorithms
{
public:
    bool randomWalk(satFormula *S, int t);

private:
    bool satisfied(struct satFormula *) const ;
    bool checkClause(struct satFormula *, int i) const ;
    int chooseL(struct satFormula*) const ;
    int chooseI(struct satFormula *, int l) const ;

};


#endif //GRAPHTHEORY_GIT_COMPLEXITYALGORITHMS_HPP