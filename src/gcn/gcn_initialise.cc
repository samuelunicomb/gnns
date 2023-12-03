#include "gcn.h"

void gcn::initialise()
{
  /*
  Initialise for the random weight experiment described in appendix
  section A1 of Kipf and Welling, ICLR (2016).
  */

  gen = mt19937(random_device{}());
  unif = uniform_real_distribution<double>(0, 1);

  readgraph();

  Y = map<int, vector<int>>{};
  Y[7]  = vector<int>{1, 0, 0, 0};
  Y[16] = vector<int>{0, 1, 0, 0};
  Y[24] = vector<int>{0, 0, 1, 0};
  Y[29] = vector<int>{0, 0, 0, 1};

  H0 = mat2d(N, vector<double>(N, 0));
  H1 = mat2d(4, vector<double>(N, 0));
  H2 = mat2d(4, vector<double>(N, 0));
  H3 = mat2d(2, vector<double>(N, 0));
  H4 = mat2d(4, vector<double>(N, 0));

  M0 = H0;
  M1 = H1;
  M2 = H2;

  W0 = mat2d(4, vector<double>(N, 0));
  W1 = mat2d(4, vector<double>(4, 0));
  W2 = mat2d(2, vector<double>(4, 0));
  W3 = mat2d(4, vector<double>(2, 0));

  dW0 = W0;
  dW1 = W1;
  dW2 = W2;
  dW3 = W3;

  for(int i = 0; i < W0.size(); ++i)
    for(int j = 0; j < W0[i].size(); ++j)
      W0[i][j] = (2 * unif(gen) - 1) * sqrt(6.0 / (N + 4));

  for(int i = 0; i < W1.size(); ++i)
    for(int j = 0; j < W1[i].size(); ++j)
      W1[i][j] = (2 * unif(gen) - 1) * sqrt(6.0 / (4 + 4));

  for(int i = 0; i < W2.size(); ++i)
    for(int j = 0; j < W2[i].size(); ++j)
      W2[i][j] = (2 * unif(gen) - 1) * sqrt(6.0 / (4 + 2));

  for(int i = 0; i < W3.size(); ++i)
    for(int j = 0; j < W3[i].size(); ++j)
      W3[i][j] = (2 * unif(gen) - 1) * sqrt(6.0 / (2 + 4));
}
