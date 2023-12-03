#include "gcn.h"

// print an arbitrary 2d matrix A
void gcn::print_matrix(const mat2d &A)
{
  for(int j = 0; j < A[0].size(); ++j)
    printf("%*d ", 9, j);
  printf("\n");

  for(int i = 0; i < A.size(); ++i){
    for(int j = 0; j < A[i].size(); ++j)
      printf("%*.6f ", 9, A[i][j]);
    printf("\n");
  }
}

// print transpose of an arbitrary 2d matrix A
void gcn::print_matrixt(const mat2d &A)
{
  for(int j = 0; j < A[0].size(); ++j){
    for(int i = 0; i < A.size(); ++i)
      printf("%*.6f ", 9, A[i][j]);
    printf("\n");
  }
}

// print an embedding H assuming it consists of two feature maps
void gcn::print_embedding(const mat2d &H)
{
  for(int j = 0; j < N; ++j){
    cout << H[0][j] << " ";
    cout << H[1][j] << " ";
    cout << "class" << nodeclass[j] << " ";
    cout << endl;
  }
}

// print the neighbour list representation of the graph
void gcn::print_graph()
{
  for(int i = 0; i < nlist.size(); ++i){
    printf("%d : ", i);
    for(auto jt : nlist[i])
      printf("%d ", jt);
    printf("\n");
  }
}
