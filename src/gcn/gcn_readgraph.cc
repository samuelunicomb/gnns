#include "gcn.h"

#include <iostream>
#include <fstream>
#include <sstream>

// read two column edgelist from file
void gcn::readgraph()
{
  string filename = "/Users/samuelunicomb/gnns/data/zachary/edges.dat";
  //string filename = "/Users/samuelunicomb/gnns/data/dummy/edges.dat";

  nlist = vector<set<int>>(100000);

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

  k = vector<int>(N);
  for(int i = 0; i < N; ++i) k[i] = nlist[i].size();

  readclasses();
}

// read node class labels from file
void gcn::readclasses()
{
  string filename = "/Users/samuelunicomb/gnns/data/zachary/classes1.dat";
  //string filename = "/Users/samuelunicomb/gnns/data/dummy/classes0.dat";

  nodeclass = vector<int>(N);

  ifstream myfile(filename);
  string line;

  while(getline(myfile, line)){
    istringstream iss(line);

    int i, c;
    if(!(iss >> i >> c)) break;

    nodeclass[i] = c;
  }
}
