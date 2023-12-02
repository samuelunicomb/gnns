#include "gcn.h"

void gcn::print_utility()
{
  cout << "hello from gcn::print_utility()" << endl;
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
