#include "mlp.h"

#include <cmath>

void mlp::train()
{
  initialise();

  X = vector<pair<double, double>>{};
  for(double x = -1; x < 1; x += 0.04){
    //double t = x * x;
    //double t = sin(3.14159 * x);
    double t = abs(x);
    //double t = x > 0 ? 1 : 0;

    X.push_back(pair<double, double>{x, t});
  }
  shuffle(X.begin(), X.end(), mt19937(random_device{}()));

  unifint = uniform_int_distribution<int>(0, X.size() - 1);

  double alpha = 0.001;
  double beta1 = 0.9;
  double beta2 = 0.999;
  double epsilon = 1e-8;

  //int nweights = weights.size();

  map<pair<int, int>, double> m, mhat, v, vhat, g;

  for(auto it : weights){
    m[it.first] = 0;
    v[it.first] = 0;
  }

  for(tcount = 1; tcount < 1000000; ++tcount){
    int ind = unifint(gen);
    forwardprop(vector<double>{X[ind].first});
    backprop(vector<double>{X[ind].second});

    g = gradient;

    for(auto it : gradient){
      pair<int, int> wji = it.first;
      m[wji] = beta1 * m[wji] + (1 - beta1) * it.second;
      v[wji] = beta2 * v[wji] + (1 - beta2) * it.second * it.second;

      mhat[wji] = m[wji] / (1 - pow(beta1, tcount));
      vhat[wji] = v[wji] / (1 - pow(beta2, tcount));

      weights[wji] -= alpha * mhat[wji] / (sqrt(vhat[wji]) + epsilon);
    }

    if(tcount % 1000 == 0){
      print_forward();
    }
  }
  print_data();
}
