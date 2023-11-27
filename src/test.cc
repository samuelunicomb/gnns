#include <iostream>

#include "gcn.h"

using namespace std;

int main ()
{
  gcn G;

  G.readgraph();

  G.print_utility();
}
