//
// Created by marco on 6/18/16.
//

#ifndef GRAPHTHEORY_GIT_COMPLEXITYALGORITHMS_HPP
#define GRAPHTHEORY_GIT_COMPLEXITYALGORITHMS_HPP

struct satFormular
{
    int k;      //k sat formula
    int m;      //m clauses per formula
    int n;      //x1, ..., xn
    bool *xVal;   //truth value of xi
    bool **xSign;   //xi or not xi
};


class ComplexityAlgorithms
{
public:
    bool randomWalk(satFormular S, int t);

private:
    bool satisfiable(struct satFormular *, int m, int k);
    bool checkClausel(struct satFormular *, int i, int);

};


#endif //GRAPHTHEORY_GIT_COMPLEXITYALGORITHMS_HPP
