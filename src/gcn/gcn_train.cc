#include "gcn.h"

void static matadd(const mat2d& A, mat2d &B)
{
  double alpha = 0.01;
  for(int i = 0; i < A.size(); ++i){
    for(int j = 0; j < A[i].size(); ++j){
      B[i][j] += -alpha * A[i][j];
    }
  }
}

void gcn::experiment01()
{
  tcount = 0;

  for(tcount = 0; tcount < 30; ++tcount){
    initialise();

    forward();
    print_fig01(H3, 0);

    forwardlinear();
    print_fig01(H3, 1);
  }
}

void gcn::experiment02()
{
  initialise();

  forward();

  for(tcount = 0; tcount < 10000; ++tcount){
    forward();
    gradient();

    if(tcount % 10 == 0) print_fig02a(H3);
    if(tcount % 1 == 0)  print_fig02b();

    matadd(dW0, W0);
    matadd(dW1, W1);
    matadd(dW2, W2);
    matadd(dW3, W3);
  }
}

void gcn::experiment03()
{
  initialise();

  forward();
  gradient();
  gradienteps();

  print_fig03a();
}
