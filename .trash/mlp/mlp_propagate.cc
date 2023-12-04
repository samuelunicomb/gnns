#include "mlp.h"

#include <cmath>

// forward pass of MLP
void mlp::forwardprop(const vector<double> &x)
{
  // input layer
  a[0] = 1;
  z[0] = a[0];
  for(int i = 0; i < x.size(); ++i){
    a[i + 1] = x[i];
    z[i + 1] = a[i + 1];
  }

  // hidden layer
  for(int l = 1; l < layers.size() - 1; ++l){
    for(int j : layers[l]){
      if(!bias[j]){
        a[j] = 0;
        for(int i : layers[l - 1])
          a[j] += weights[pair<int, int>{j, i}] * z[i];
        z[j] = tanh(a[j]);
      }
    }
  }

  y = vector<double>(dimout, 0);

  // output layer
  for(int k : layers[2]){
    a[k] = 0;
    for(int j : layers[1]){
      a[k] += weights[pair<int, int>{k, j}] * z[j];
    }
    z[k] = a[k];
    y[0] = a[k];
  }
}

// backward pass to compute gradient
void mlp::backprop(const vector<double> &t)
{
  // delta, output layer
  for(int k : layers[2]){
    delta[k] = y[0] - t[0];
  }

  // delta, hidden layers
  for(int l = 1; l > 0; --l){
    for(int j : layers[l]){
      delta[j] = 0;
      for(int k : layers[l + 1])
        delta[j] += weights[pair<int, int>{k, j}] * delta[k];
      delta[j] *= 1 - tanh(a[j]) * tanh(a[j]);
    }
  }

  // delta, input layer
  for(int j : layers[0]){
    delta[j] = 0;
    for(int k : layers[1]){
      if(!bias[k])
        delta[j] += weights[pair<int, int>{k, j}] * delta[k];
    }
  }

  // fill gradient vector
  for(auto it : weights){
    int j = it.first.first;
    int i = it.first.second;
    gradient[it.first] =  delta[j] * z[i];
  }
}
