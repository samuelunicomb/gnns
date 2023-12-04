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

    map<int, vector<int>> Y;
    map<int, set<int>> classmap;

    void readgraph();
    void readclasses();

    vector<int> k;
    mat2d W0, W1, W2, W3;
    mat2d dW0, dW1, dW2, dW3, dW0num, dW1num, dW2num, dW3num;
    mat2d dW0m, dW1m, dW2m, dW3m, dW0v, dW1v, dW2v, dW3v;
    mat2d H0, H1, H2, H3, H4, M0, M1, M2, M3, H0t, H1t, H2t, H3t, H4t;
    mat2d del1, del2, del3, del4;
    mat2d I;
    double L;

    void forward();
    void forwardlinear();
    void initialise();
    void reset();
    void dropout(mat2d&, const double&);
    void dropout(mat2d&, mat2d&, const double&);
    void aggregate(const mat2d&, mat2d&);
    void equate(const mat2d&, mat2d&);
    void nonlinearity(const mat2d&, mat2d&);
    void linearity(const mat2d&, mat2d&);
    void softmax(const mat2d&, mat2d&);
    void crossentropy();

    int tcount;
    void experiment01();
    void experiment02();
    void experiment03();

    double epsilon;
    void gradient();
    void gradienteps();
    void gradienteps(const int&, const int&, const int&);
    void wepsilon(const int&, const int&, const int&, const double&);
    void gradienterr(double&);
    void erroranalysis();

    void print_graph();
    void print_matrix(const mat2d&);
    void print_matrixt(const mat2d&);

    void print_fig01(const mat2d&, const int&);
    void print_fig02a(const mat2d&);
    void print_fig02b();
    void print_fig03a();

    mt19937 gen;
    uniform_real_distribution<double> unif;
};
#endif
