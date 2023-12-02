#include "gcn.h"

#include <iostream>
#include <fstream>
#include <sstream>

// read two column edgelist from file
void gcn::readgraph()
{
  nlist = vector<set<int>>(100000);

  string filename = "/Users/samuelunicomb/kipf/data/zachary/edges.dat";
  ifstream myfile(filename);
  string line;

  while(getline(myfile, line)){
    istringstream iss(line);

    int u, v;
    if(!(iss >> u >> v)) break;

    nlist[u].insert(v);
    nlist[v].insert(u);
  }
  
  while(nlist.back().size() == 0) nlist.pop_back();

  N = nlist.size();
}
