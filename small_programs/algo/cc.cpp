#include <iostream>
#include <graph.h>
#include <gtraverse.h>
#include <sequtils.h>

class ConnectedCompVisitor : public NodeVisitor {
private:
  std::vector<bool> visited;
  std::vector<int> comp;
public:
  ConnectedCompVisitor(Graph *g) : NodeVisitor(g) {
    int num_nodes = g->getNumNodes();
    visited.resize(num_nodes);
    for(int i = 0; i < num_nodes; ++i) {
      visited[i] = false;
    }
  }

  virtual void previsit(int node) {
  }

  virtual void postvisit(int node) {
    visited[node] = true;
    comp.push_back(node);
  }

  int  getNextUnvisited() {
    int num_nodes = graph->getNumNodes();
    for(int i=0; i < num_nodes; ++i) {
      if (!visited[i])
	return i;
    }
    return -1;
  }
  
  int reset() {
    comp.clear();
  }

  std::vector<int> getComponent() {
    return comp;
  }
};

std::vector<std::vector<int>> findConnectedComponents(Graph *g)
{
  std::vector<std::vector<int>> ret;
  int node = 0;
  DfsSearch dfs(g);
  ConnectedCompVisitor *v = new ConnectedCompVisitor(g);
  dfs.setVisitor(v);
  while((node = v->getNextUnvisited()) != -1) {
    v->reset();
    dfs.search_from(node);
    auto comp = v->getComponent();
    ret.push_back(comp);
    std::cout << std::endl;
  }
  return ret;
}

int main(int argc, char **argv)
{
  Graph *g = makeRandomGraph<Graph>(10, 7);
  auto ret = findConnectedComponents(g);
  for(auto iter = ret.begin();
      iter != ret.end();
      ++iter)
    print_seq(*iter);
  g->write_dot_file("/tmp/g.dot");
}
