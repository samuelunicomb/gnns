#include "gcn.h"

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

// set elements of A to zero with probability p
void gcn::dropout(mat2d &A, const double &p)
{
  for(int i = 0; i < A.size(); ++i){
    for(int j = 0; j < A[i].size(); ++j){
      if(unif(gen) < p) A[i][j] = 0;
    }
  }
}

void gcn::dropout(mat2d &A, mat2d &B, const double &p)
{
  for(int i = 0; i < A.size(); ++i){
    for(int j = 0; j < A[i].size(); ++j){
      if(unif(gen) < p){
        A[i][j] = 0;
        B[i][j] = 0;
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

// element-wise computation of nonlinearities
void gcn::linearity(const mat2d &Ht, mat2d &H)
{
  for(int i = 0; i < H.size(); ++i)
    for(int j = 0; j < H[i].size(); ++j)
      H[i][j] = Ht[i][j];
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

void gcn::forwardlinear()
{
  reset();

  // l = 0
  aggregate(H0, M0);

  // l = 1
  matmul(W0, M0, H1t);
  linearity(H1t, H1);
  aggregate(H1, M1);

  // l = 2
  matmul(W1, M1, H2t);
  linearity(H2t, H2);
  aggregate(H2, M2);

  // l = 3
  matmul(W2, M2, H3t);
  linearity(H3t, H3);
  equate(H3, M3);

  // l = 4
  matmul(W3, M3, H4t);
  softmax(H4t, H4);

  crossentropy();
}
