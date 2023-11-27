#ifndef MLP_H_
#define MLP_H_

#include <vector>
#include <map>
#include <set>
#include <random>
#include <iostream>

using namespace std;

class mlp
{
  public:
    mlp(){};

    int n, dimin, dimout, numhidden;

    vector<double> a, z, delta;
    vector<int> bias, hidden;

    vector<pair<double, double>> X;

    vector<double> x, y;

    map<pair<int, int>, double> weights, partiale;
    vector<set<int>> layers;

    void initialise();
    void forwardprop(const vector<double>&);
    void backprop(const vector<double>&);
    void train();

    void print_forward();
    void print_weights();

    mt19937 gen;
    uniform_real_distribution<double> unif;
};
#endif
