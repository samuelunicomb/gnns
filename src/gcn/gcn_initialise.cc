#include "gcn.h"

void gcn::initialise()
{
  /*
  Initialise for the random weight experiment described in appendix 
  section A1 of Kipf and Welling (2016). 
  */

  gen = mt19937(random_device{}());
  unif = uniform_real_distribution<double>(0, 1);

  readgraph();

  H0 = mat2d(N, vector<double>(N, 0));
  H1 = mat2d(4, vector<double>(N, 0));
  H2 = mat2d(4, vector<double>(N, 0));
  H3 = mat2d(2, vector<double>(N, 0));

  M0 = mat2d(N, vector<double>(N, 0));
  M1 = mat2d(4, vector<double>(N, 0));
  M2 = mat2d(4, vector<double>(N, 0));

  W0 = vector<vector<double>> (4, vector<double>(N, 0));
  W1 = vector<vector<double>> (4, vector<double>(4, 0));
  W2 = vector<vector<double>> (2, vector<double>(4, 0));

  for(int i = 0; i < W0.size(); ++i)
    for(int j = 0; j < W0[i].size(); ++j)
      W0[i][j] = (2 * unif(gen) - 1) * sqrt(6.0 / (N + 4));

  for(int i = 0; i < W1.size(); ++i)
    for(int j = 0; j < W1[i].size(); ++j)
      W1[i][j] = (2 * unif(gen) - 1) * sqrt(6.0 / (4 + 4));
  
  for(int i = 0; i < W2.size(); ++i)
    for(int j = 0; j < W2[i].size(); ++j)
      W2[i][j] = (2 * unif(gen) - 1) * sqrt(6.0 / (4 + 2));
}
