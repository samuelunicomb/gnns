#include "mlp.h"

void mlp::print_forward()
{
  for(double x = -10; x < 10; x += 0.1){
    forwardprop(vector<double>{x});

    cout << x << " ";
    cout << y[0] << " ";
    cout << endl;
  }
}
