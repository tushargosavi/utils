#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <sequtils.h>
#include <graph.h>

// add a edge between two nodes.
// in case of undirected graph add two edges.
bool Graph::add_edge(int start, int end) {
  auto iter = std::find(edgelist[start].begin(),
			edgelist[start].end(),
			end);
  if (iter == edgelist[start].end()) {
    edgelist[start].push_back(end);
    edgelist[end].push_back(start);
    numEdges++;
    return true;
  }
  return false;
}

// Return true if there is a edge from start to end.
bool Graph::isConnected(int start, int end) {
  auto iter = std::find(edgelist[start].begin(),
			edgelist[start].end(),
			end);
  if(iter == edgelist[start].end())
    return false;
  return true;
}

void Graph::write_dot_file(std::string fname) {
  // write list of nodes
  std::ofstream out;
  out.open(fname);
  out << "graph G {";
  for(int i = 0; i < numNodes; ++i) {
    for(auto temp = edgelist[i].begin();
	temp != edgelist[i].end();
	++temp) {
      if (i < *temp)
	out << i << "--" << *temp << std::endl;
    }
  }
  out << "}";
  out.close();
}

bool DiGraph::add_edge(int start, int end) {
  auto ptr = std::find(edgelist[start].begin(),
		       edgelist[start].end(),
		       end);
  if (ptr == edgelist[start].end()) {
    edgelist[start].push_back(end);
    numEdges++;
    return true;
  }
  return false;
}

void DiGraph::write_dot_file(std::string fname) {
  // write list of nodes
  std::ofstream out;
  out.open(fname);
  out << "digraph G {";
  for(int i = 0; i < numNodes; ++i) {
    for(auto temp = edgelist[i].begin();
	temp != edgelist[i].end();
	++temp) {
      out << i << "->" << *temp << std::endl;
    }
  }
  out << "}";
  out.close();
}

// Read the graph from file.
void Graph::readFromFile(std::string filename)
{
  std::ifstream in;
  std::string line;
  int node = 0;
  int end = 0;

  in.open(filename);
  node = 0;
  while (!in.eof()) {
    std::getline(in, line);
    if (line == "") {
      node++;
      continue;
    }
    std::istringstream sin(line);
    while(!sin.eof()) {
      sin >> end;
      add_edge(node, end);
    }
    node++;
  }
  in.close();
}

// Write a file in format which can be read back using
// readFromFile
void Graph::writeToFile(std::string filename)
{
  std::ofstream out;
  out.open(filename);
  for(int i = 0; i < numNodes; ++i) {
    for(auto temp = edgelist[i].begin();
	temp != edgelist[i].end();
	++temp) {
      out << *temp;
    }
    out << std::endl;
  }
}


Graph *reverseGraph(Graph *g)
{
  int num_nodes;
  Graph * ret = NULL;

  num_nodes = g->getNumNodes();
  ret = new Graph(num_nodes);

  for(int i= 0; i < num_nodes; ++i) {
    auto neighbours = g->neighbours(i);
    for(auto iter = neighbours.begin();
	iter != neighbours.end();
	++iter)
      ret->add_edge(*iter, i);
  }
  return ret;
}
