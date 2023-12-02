#include "gcn.h"

#include <cmath>

// compute C = AB, for matrices A, B, C
static void matmul(const mat2d &A, const mat2d &B, mat2d &C)
{
  for(int i = 0; i < C.size(); ++i){
    for(int j = 0; j < C[i].size(); ++j){
      C[i][j] = 0;
      for(int k = 0; k < A[i].size(); ++k){
        C[i][j] += A[i][k] * B[k][j];
      }
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

// compute the element-wise nonlinearities
void gcn::nonlinearity(mat2d &H)
{
  for(int i = 0; i < H.size(); ++i)
    for(int j = 0; j < H[i].size(); ++j)
      H[i][j] = tanh(H[i][j]);
}

void gcn::train()
{
  initialise();

  for(int i = 0; i < H0.size(); ++i) H0[i][i] = 1;

  aggregate(H0, M0);

  cout << "initial" << endl;
  cout << "=====================================" << endl;
  print_matrix(H0);
  cout << endl;
  print_matrix(W0);
  cout << endl;
  print_matrix(M0);
  cout << endl;

  matmul(W0, H0, H1);
  nonlinearity(H1);

  cout << "final" << endl;
  cout << "=====================================" << endl;
  print_matrix(H1);
  cout << endl;

  //aggregate(H1, M1);
  //matmul(W1, H1, H2);
  //nonlinearity(H2);

  //aggregate(H2, M2);
  //matmul(W2, H2, H3);
  //nonlinearity(H3);

  //for(int j = 0; j < N; ++j){
  //  cout << H3[0][j] << " ";
  //  cout << H3[1][j] << " ";
  //  cout << "type" << nodeclass[j] << " ";
  //  cout << endl;
  //}
}
