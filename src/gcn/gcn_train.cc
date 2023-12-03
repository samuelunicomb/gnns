#include "gcn.h"

//#include <cmath>  // tanh

// compute C = AB, for matrices A, B, C
static void matmul(const mat2d &A, const mat2d &B, mat2d &C)
{
  for(int i = 0; i < C.size(); ++i){
    for(int j = 0; j < C[i].size(); ++j){
      C[i][j] = 0;
      for(int k = 0; k < A[i].size(); ++k)
        C[i][j] += A[i][k] * B[k][j];
    }
  }
}

// set columns of M to linear combinations of columns of H
void gcn::aggregate(const mat2d &H, mat2d &M)
{
  for(int i = 0; i < N; ++i){
    // column i of M
    vec1d Mcoli(M.size());

    // set column i of row M to column i of H scaled by ki + 1
    for(int l = 0; l < H.size(); ++l)
      Mcoli[l] = H[l][i] / (k[i] + 1);

    // for all neighbours j of node i add the scaled embedding to column i of M
    for(int j : nlist[i]){
      for(int l = 0; l < H.size(); ++l)
        Mcoli[l] += H[l][j] / sqrt((k[i] + 1) * (k[j] + 1));
    }

    for(int l = 0; l < M.size(); ++l)
      M[l][i] = Mcoli[l];
  }
}

// set M = H
void gcn::equate(const mat2d &H, mat2d &M)
{
  M = H;
}

// element-wise computation of nonlinearities
void gcn::nonlinearity(const mat2d &Ht, mat2d &H)
{
  for(int i = 0; i < H.size(); ++i)
    for(int j = 0; j < H[i].size(); ++j)
      H[i][j] = tanh(Ht[i][j]);
}

// column-wise application of softmax
void gcn::softmax(const mat2d &Ht, mat2d &H)
{
  for(int j = 0; j < Ht[0].size(); ++j){
    double norm = 0;
    for(int i = 0; i < Ht.size(); ++i)
      norm += exp(Ht[i][j]);

    for(int i = 0; i < H.size(); ++i)
      H[i][j] = exp(Ht[i][j]) / norm;
  }
}

// cross-entropy loss of softmax output layer
void gcn::crossentropy()
{
  L = 0;
  for(auto it : Y){
    int j = it.first;
    for(int i = 0; i < H4.size(); ++i){
      L -= Y[j][i] * log(H4[i][j]);
    }
  }
}

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
  for(int j = 0; j < del3[0].size(); ++j){ // column j
    for(int i = 0; i < del3.size(); ++i){ // row i
      for(int k = 0; k < 4; ++k){
        del3[i][j] += W3[k][i] * del4[k][j];
      }
      del3[i][j] *= 1 - tanh(H3t[i][j]) * tanh(H3t[i][j]);
    }
  }

  // l = 2
  for(int j = 0; j < del2[0].size(); ++j){ // column j
    for(int i = 0; i < del2.size(); ++i){ // row i
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
  for(int j = 0; j < del1[0].size(); ++j){ // column j
    for(int i = 0; i < del1.size(); ++i){ // row i

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

void gcn::forward()
{
  reset();

  // l = 0
  aggregate(H0, M0);

  // l = 1
  matmul(W0, M0, H1t);
  nonlinearity(H1t, H1);
  aggregate(H1, M1);

  // l = 2
  matmul(W1, M1, H2t);
  nonlinearity(H2t, H2);
  aggregate(H2, M2);

  // l = 3
  matmul(W2, M2, H3t);
  nonlinearity(H3t, H3);
  equate(H3, M3);

  // l = 4
  matmul(W3, M3, H4t);
  softmax(H4t, H4);

  crossentropy();
}

void gcn::numgradient(const int &i, const int &j, double &E)
{
  double eps = 1e-3;
  double w = W0[i][j];

  W0[i][j] = w + eps;
  forward();
  double Ep = L;

  W0[i][j] = w - eps;
  forward();
  double Em = L;

  E = (Ep - Em) / (2 * eps);
}

void gcn::train()
{
  initialise();

  double E;

  forward();
  gradient();

  //print_matrix(dW0);
  //cout << endl;
  //numgradient(0, 0, E); printf("%*.6f ",  9, E);
  //numgradient(0, 1, E); printf("%*.6f ",  9, E);
  //numgradient(0, 2, E); printf("%*.6f ",  9, E);
  //numgradient(0, 3, E); printf("%*.6f ",  9, E);
  //numgradient(0, 4, E); printf("%*.6f ",  9, E);
  //numgradient(0, 5, E); printf("%*.6f ",  9, E);
  //numgradient(0, 6, E); printf("%*.6f ",  9, E);
  //numgradient(0, 7, E); printf("%*.6f\n", 9, E);
  //numgradient(1, 0, E); printf("%*.6f ",  9, E);
  //numgradient(1, 1, E); printf("%*.6f ",  9, E);
  //numgradient(1, 2, E); printf("%*.6f ",  9, E);
  //numgradient(1, 3, E); printf("%*.6f ",  9, E);
  //numgradient(1, 4, E); printf("%*.6f ",  9, E);
  //numgradient(1, 5, E); printf("%*.6f ",  9, E);
  //numgradient(1, 6, E); printf("%*.6f ",  9, E);
  //numgradient(1, 7, E); printf("%*.6f\n", 9, E);
  //numgradient(2, 0, E); printf("%*.6f ",  9, E);
  //numgradient(2, 1, E); printf("%*.6f ",  9, E);
  //numgradient(2, 2, E); printf("%*.6f ",  9, E);
  //numgradient(2, 3, E); printf("%*.6f ",  9, E);
  //numgradient(2, 4, E); printf("%*.6f ",  9, E);
  //numgradient(2, 5, E); printf("%*.6f ",  9, E);
  //numgradient(2, 6, E); printf("%*.6f ",  9, E);
  //numgradient(2, 7, E); printf("%*.6f\n", 9, E);
  //numgradient(3, 0, E); printf("%*.6f ",  9, E);
  //numgradient(3, 1, E); printf("%*.6f ",  9, E);
  //numgradient(3, 2, E); printf("%*.6f ",  9, E);
  //numgradient(3, 3, E); printf("%*.6f ",  9, E);
  //numgradient(3, 4, E); printf("%*.6f ",  9, E);
  //numgradient(3, 5, E); printf("%*.6f ",  9, E);
  //numgradient(3, 6, E); printf("%*.6f ",  9, E);
  //numgradient(3, 7, E); printf("%*.6f\n", 9, E);

  //print_matrix(dW1);
  //cout << endl;
  //numgradient(0, 0, E); printf("%*.6f ",  9, E);
  //numgradient(0, 1, E); printf("%*.6f ",  9, E);
  //numgradient(0, 2, E); printf("%*.6f ",  9, E);
  //numgradient(0, 3, E); printf("%*.6f\n", 9, E);
  //numgradient(1, 0, E); printf("%*.6f ",  9, E);
  //numgradient(1, 1, E); printf("%*.6f ",  9, E);
  //numgradient(1, 2, E); printf("%*.6f ",  9, E);
  //numgradient(1, 3, E); printf("%*.6f\n", 9, E);
  //numgradient(2, 0, E); printf("%*.6f ",  9, E);
  //numgradient(2, 1, E); printf("%*.6f ",  9, E);
  //numgradient(2, 2, E); printf("%*.6f ",  9, E);
  //numgradient(2, 3, E); printf("%*.6f\n", 9, E);
  //numgradient(3, 0, E); printf("%*.6f ",  9, E);
  //numgradient(3, 1, E); printf("%*.6f ",  9, E);
  //numgradient(3, 2, E); printf("%*.6f ",  9, E);
  //numgradient(3, 3, E); printf("%*.6f\n", 9, E);

  //print_matrix(dW2);
  //cout << endl;
  //numgradient(0, 0, E); printf("%*.6f ",  9, E);
  //numgradient(0, 1, E); printf("%*.6f ",  9, E);
  //numgradient(0, 2, E); printf("%*.6f ",  9, E);
  //numgradient(0, 3, E); printf("%*.6f\n", 9, E);
  //numgradient(1, 0, E); printf("%*.6f ",  9, E);
  //numgradient(1, 1, E); printf("%*.6f ",  9, E);
  //numgradient(1, 2, E); printf("%*.6f ",  9, E);
  //numgradient(1, 3, E); printf("%*.6f\n", 9, E);

  //print_matrix(dW3);
  //cout << endl;
  //numgradient(0, 0, E); printf("%*.6f ",  9, E);
  //numgradient(0, 1, E); printf("%*.6f\n", 9, E);
  //numgradient(1, 0, E); printf("%*.6f ",  9, E);
  //numgradient(1, 1, E); printf("%*.6f\n", 9, E);
  //numgradient(2, 0, E); printf("%*.6f ",  9, E);
  //numgradient(2, 1, E); printf("%*.6f\n", 9, E);
  //numgradient(3, 0, E); printf("%*.6f ",  9, E);
  //numgradient(3, 1, E); printf("%*.6f\n", 9, E);

  //print_embedding(H3);
}
