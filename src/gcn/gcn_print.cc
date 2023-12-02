#include "gcn.h"

void gcn::print_utility()
{
  cout << "hello from gcn::print_utility()" << endl;
}

void gcn::print_matrix(const mat2d &A)
{
  for(int i = 0; i < A.size(); ++i){
    for(int j = 0; j < A[i].size(); ++j){
      printf("%*.4f ", 7, A[i][j]);
    }
    printf("\n");
  }
}

void gcn::print_graph()
{
  for(int i = 0; i < nlist.size(); ++i){
    cout << i << " : ";
    for(auto jt : nlist[i]){
      cout << jt << " ";
    }
    cout << endl;
  }
}
