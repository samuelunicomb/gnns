#include "mlp.h"

#include <cmath>
#include <cassert>

void mlp::initialise()
{
  dimin = 1;                  // dimension of input
  dimout = 1;                 // dimension of output
  hidden = vector<int>{3};    // dimension of hidden layers
  numhidden = hidden.size();  // number of hidden layers

  n = dimin + dimout + 1;
  for(int i : hidden)
    n += i + 1;

  a = vector<double> (n, 1);
  z = vector<double> (n, 1);
  delta = vector<double> (n, 1);
  bias = vector<int>(n, 0);

  weights = map<pair<int, int>, double>{};
  layers = vector<set<int>>(2 + hidden.size());

  int index = 0;

  // input layer
  for(int i = 0; i < dimin + 1; ++i){
    if(i == 0) bias[index] = 1;
    layers[0].insert(index);
    ++index;
  }

  // hidden layers
  for(int i = 0; i < hidden.size(); ++i){
    for(int j = 0; j < hidden[i] + 1; ++j){
      if(j == 0) bias[index] = 1;
      layers[i + 1].insert(index);
      ++index;
    }
  }

  // output layer
  for(int i = 0; i < dimout; ++i){
    layers[1 + numhidden].insert(index);
    ++index;
  }

  assert(n == index);

  gen = mt19937(random_device{}());
  unif = uniform_real_distribution<double>(0, 1);

  // construct and initialise weights
  for(int l = 1; l < layers.size(); ++l){
    for(int j : layers[l]){
      if(!bias[j]){
        for(int i : layers[l - 1]){
          weights[pair<int, int>{j, i}] = unif(gen);
        }
      }
    }
  }

  // construct error gradient
  partiale = map<pair<int, int>, double>{};

  for(auto it : weights)
    partiale[it.first] = 0;  
}
