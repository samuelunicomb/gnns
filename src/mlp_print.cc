#include "mlp.h"

void mlp::print_forward()
{
  for(double x = -1; x < 1; x += 0.005){
    forwardprop(vector<double>{x});

    cout << tcount << " ";
    cout << "nn ";
    cout << x << " ";
    cout << y[0] << " ";
    cout << z[3] << " ";
    cout << z[4] << " ";
    cout << z[5] << " ";
    cout << endl;
  }
}

void mlp::print_data()
{
  for(auto it : X){
    cout << "0 " << " ";
    cout << "data " << " ";
    cout << it.first << " ";
    cout << it.second << " ";
    cout << endl;
  }
}
