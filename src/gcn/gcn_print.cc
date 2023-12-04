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

void gcn::print_fig01(const mat2d &H, const int &f)
{
  for(int j = 0; j < N; ++j){
    printf("%d ", tcount);
    if(f == 0) printf("nonlinear ");
    if(f == 1) printf("linear ");
    printf("%f ", H[0][j]);
    printf("%f ", H[1][j]);
    printf("%d ", nodeclass[j]);
    printf("\n");
  }
}

void gcn::print_fig02a(const mat2d &H)
{
  for(int j = 0; j < N; ++j){
    printf("%d ", tcount);
    printf("embedding ");
    printf("%f ", H[0][j]);
    printf("%f ", H[1][j]);
    printf("%d ", nodeclass[j]);
    printf("\n");
  }
}

void gcn::print_fig02b()
{
  printf("%d ", tcount);
  printf("loss ");
  printf("%f ", L);
  printf("\n");
}
