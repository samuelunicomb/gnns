#include "mlp.h"

#include <cmath>

void mlp::train()
{
  initialise();

  X = vector<pair<double, double>>{};
  for(double x = -2; x < 2; x += 0.1){
    double t = abs(x);
    X.push_back(pair<double, double>{x, t});
  }
  shuffle(X.begin(), X.end(), mt19937(random_device{}()));

  double alpha = 1e-3;
  double beta1 = 0.9;
  double beta2 = 0.999;
  double epsilon = 1e-8;

  int tmax = 100;
  int t = 0;
  vector<double> m(tmax, 0);
  vector<double> v(tmax, 0);

  for(int t = 0; t < 10; ++t){
    //cout << X[t].first << " ";
    //cout << X[t].second << " ";
    //cout << endl;

    forwardprop(vector<double>{X[t].first});
    backprop(vector<double>{X[t].second});

    //cout << it.first << " ";
    //cout << it.second << " | ";
    //for(auto jt : partiale) cout << jt.first.first << " ";
    //cout << endl;
  }

}
