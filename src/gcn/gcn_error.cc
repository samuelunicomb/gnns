#include "gcn.h"

void gcn::erroranalysis()
{
  initialise();

  forward();

  epsilon = 1e-4;

  gradient();
  gradienteps();

  double e;
  gradienterr(e);

  printf("%e is error\n", e);
}
