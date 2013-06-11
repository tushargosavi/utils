#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Graph {
public:
  int numNodes;
  int numEdges;
  std::vector<std::vector<int>> edgelist;

public:

  Graph(int n):numNodes(n) {
    // allocate memory so that accessing them
    // will not cause a fault.
   edgelist.resize(n);
   numEdges = 0;
  }
   
  virtual bool add_edge(int start, int end);
  virtual void write_dot_file(std::string fname);
  virtual void readFromFile(std::string fname);
  virtual void writeToFile(std::string fname);

  int getNumNodes() { return numNodes; }
  int getNumEdges() { return numEdges; }
  std::vector<int> neighbours(int n) { return edgelist[n]; }
  bool isConnected(int start, int end);
};

class DiGraph : public Graph
{
public:
  DiGraph(int n):Graph(n) {}
  virtual bool add_edge(int start, int end);
  virtual void write_dot_file(std::string fname);
};

template<typename T>
T *makeRandomGraph(int numNodes, int numEdges)
{
  T *g = new T(numNodes);
  for(int k = 0; k < numEdges;) {
    int i = rand() % numNodes;
    int j = rand() % numNodes;
    
    // inc edges if it is added.
    if (g->add_edge(i, j))
      k++;
  }
  return g;
}


// reverse edges of a directed graph.
Graph *reverseGraph(Graph *g);

#endif
