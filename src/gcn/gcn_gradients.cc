#include "gcn.h"

#include <cmath>

// computes gradient via backpropagation
void gcn::gradient()
{
  // l = 4
  for(auto it : Y){
    int j = it.first;
    for(int i = 0; i < del4.size(); ++i){
      del4[i][j] = H4[i][j] - Y[j][i];
    }
  }

  // l = 3
  for(int j = 0; j < del3[0].size(); ++j){
    for(int i = 0; i < del3.size(); ++i){
      for(int k = 0; k < 4; ++k){
        del3[i][j] += W3[k][i] * del4[k][j];
      }
      del3[i][j] *= 1 - tanh(H3t[i][j]) * tanh(H3t[i][j]);
    }
  }

  // l = 2
  for(int j = 0; j < del2[0].size(); ++j){
    for(int i = 0; i < del2.size(); ++i){
      // ego sum
      double suma = 0;
      for(int k = 0; k < 2; ++k){
        suma += W2[k][i] * del3[k][j];
      }
      suma *= 1 - tanh(H2t[i][j]) * tanh(H2t[i][j]);
      suma /= k[j] + 1;

      // neighbour sum
      double sumb = 0;
      for(int l : nlist[j]){
        double sumc = 0;
        for(int k = 0; k < 2; ++k){
          sumc += W2[k][i] * del3[k][l];
        }
        sumc *= 1 - tanh(H2t[i][j]) * tanh(H2t[i][j]);
        sumc /= sqrt((k[j] + 1) * (k[l] + 1));

        sumb += sumc;
      }
      del2[i][j] = suma + sumb;
    }
  }

  // l = 1
  for(int j = 0; j < del1[0].size(); ++j){
    for(int i = 0; i < del1.size(); ++i){

      // ego sum
      double suma = 0;
      for(int k = 0; k < 4; ++k){
        suma += W1[k][i] * del2[k][j];
      }
      suma *= 1 - tanh(H1t[i][j]) * tanh(H2t[i][j]);
      suma /= k[j] + 1;


      // neighbour sum
      double sumb = 0;
      for(int l : nlist[j]){
        double sumc = 0;
        for(int k = 0; k < 4; ++k){
          sumc += W1[k][i] * del2[k][l];
        }
        sumc *= 1 - tanh(H1t[i][j]) * tanh(H1t[i][j]);
        sumc /= sqrt((k[j] + 1) * (k[l] + 1));

        sumb += sumc;
      }
      del1[i][j] = suma + sumb;
    }
  }

  for(int i = 0; i < 4; ++i){
    for(int j = 0; j < 2; ++j){
      dW3[i][j] = 0;
      for(int k = 0; k < N; ++k){
        dW3[i][j] += del4[i][k] * M3[j][k];
      }
    }
  }

  for(int i = 0; i < 2; ++i){
    for(int j = 0; j < 4; ++j){
      dW2[i][j] = 0;
      for(int k = 0; k < N; ++k){
        dW2[i][j] += del3[i][k] * M2[j][k];
      }
    }
  }

  for(int i = 0; i < 4; ++i){
    for(int j = 0; j < 4; ++j){
      dW1[i][j] = 0;
      for(int k = 0; k < N; ++k){
        dW1[i][j] += del2[i][k] * M1[j][k];
      }
    }
  }

  for(int i = 0; i < 4; ++i){
    for(int j = 0; j < N; ++j){
      dW0[i][j] = 0;
      for(int k = 0; k < N; ++k){
        dW0[i][j] += del1[i][k] * M0[j][k];
      }
    }
  }
}

void gcn::gradienteps(const int &f, const int &i, const int &j)
{
  double E = 0;

  //epsilon = 1e-4;
  wepsilon(f, i, j, epsilon);
  forward();
  E += L;

  wepsilon(f, i, j, -2 * epsilon);
  forward();
  E -= L;

  wepsilon(f, i, j, epsilon);
  E /= 2 * epsilon;

  switch(f){
    case 0:
      dW0num[i][j] = E; break;
    case 1:
      dW1num[i][j] = E; break;
    case 2:
      dW2num[i][j] = E; break;
    case 3:
      dW3num[i][j] = E; break;
  }
}

void gcn::wepsilon(const int &f, const int &i, const int &j, const double &e)
{
  switch(f){
    case 0:
      W0[i][j] += e; break;
    case 1:
      W1[i][j] += e; break;
    case 2:
      W2[i][j] += e; break;
    case 3:
      W3[i][j] += e; break;
  }
}

void gcn::gradienteps()
{
  //epsilon = 1e-1;

  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < N; ++j)
      gradienteps(0, i, j);

  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 4; ++j)
      gradienteps(1, i, j);

  for(int i = 0; i < 2; ++i)
    for(int j = 0; j < 4; ++j)
      gradienteps(2, i, j);

  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 2; ++j)
      gradienteps(3, i, j);
}

void gcn::gradienterr(double &e)
{
  e = 0;

  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < N; ++j){
      //cout << abs(dW0[i][j] - dW0num[i][j]) << " " << dW0[i][j] << " " << dW0num[i][j] << " " << i << " " << j << " 0 is err" << endl;
      e += pow(dW0[i][j] - dW0num[i][j], 2);
    }

  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 4; ++j){
      //cout << abs(dW1[i][j] - dW1num[i][j]) << " " << dW1[i][j] << " " << dW1num[i][j] << " " << i << " " << j << " 1 is err" << endl;
      e += pow(dW1[i][j] - dW1num[i][j], 2);
    }

  for(int i = 0; i < 2; ++i)
    for(int j = 0; j < 4; ++j){
      //cout << abs(dW2[i][j] - dW2num[i][j]) << " " << dW2[i][j] << " " << dW2num[i][j] << " " << i << " " << j << " 2 is err" << endl;
      e += pow(dW2[i][j] - dW2num[i][j], 2);
    }

  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 2; ++j){
      //cout << abs(dW3[i][j] - dW3num[i][j]) << " " << dW3[i][j] << " " << dW3num[i][j] << " " << i << " " << j << " 3 is err" << endl;
      e += pow(dW3[i][j] - dW3num[i][j], 2);
    }

  e = sqrt(e) / (N * 4 + 4 * 4 + 4 * 2 + 2 * 4);
}
