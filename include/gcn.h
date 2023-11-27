#ifndef GCN_H_
#define GCN_H_

#include <vector>
#include <set>
#include <map>
#include <random>
#include <iostream>

using namespace std;

class gcn
{
  public:
    gcn(){};

    int N;
    vector<set<int>> nlist;
    map<int, int> partial{{0, 0}, {16, 1}, {32, 2}, {33, 3}};
    void readgraph();

    vector<vector<double>> W0, W1, W2;
    vector<vector<double>> X;
    vector<vector<double>> A, Atilde, Ahat;

    void print_utility();

    mt19937 gen;
    uniform_real_distribution<double> unif;
};
#endif
