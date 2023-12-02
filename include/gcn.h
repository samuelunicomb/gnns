#ifndef GCN_H_
#define GCN_H_

#include <vector>
#include <set>
#include <map>
#include <random>
#include <iostream>

using namespace std;

typedef vector<vector<double>> mat2d;
typedef vector<double> vec1d;

class gcn
{
  public:
    gcn(){};

    int N;
    vector<set<int>> nlist;
    vector<int> nodeclass;
    map<int, int> partial{{0, 0}, {16, 1}, {32, 2}, {33, 3}};

    void readgraph();
    void readclasses();

    vector<int> k;  // node degrees
    vector<vector<double>> W0, W1, W2;
    vector<vector<double>> X;
    vector<vector<double>> M;

    void initialise();
    void aggregate(const mat2d&, mat2d&);
    void nonlinearity(mat2d&);
    void train();

    void print_utility();
    void print_graph();

    mt19937 gen;
    uniform_real_distribution<double> unif;
};
#endif
