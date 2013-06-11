#ifndef GTRAVERSE_H
#define GTRAVERSE_H

#include <vector>
#include <queue>
#include <graph.h>
#include <sequtils.h>

class NodeVisitor;

class GraphSearch {
 protected:
  // The pointer to graph being traverse.
  Graph *graph;

  // visitor
  NodeVisitor *visitor;
  
  // order in which nodes are visited.
  std::vector<int> order;

 public:
  GraphSearch(Graph *g):graph(g),visitor(NULL) {}
  void setVisitor(NodeVisitor *v) { visitor = v; }
  virtual void search_from(int node) = 0;
  virtual void print_order() {
    print_seq(order);
  }
};

class DfsSearch : public GraphSearch
{
 private:
  std::vector<bool> visited;
 public:
  DfsSearch(Graph *g);
  
  void search_from(int node);
  void search_from_iter(int node);
};

class BfsSearch : public GraphSearch
{
private:
  std::vector<bool> visited;
  std::queue<int> queue;

public:
  BfsSearch(Graph *g);
  virtual void search_from(int node);
};

class NodeVisitor {
 protected:
  Graph *graph;
 public:
  NodeVisitor(Graph *g):graph(g) {}
  virtual void previsit(int node) = 0;
  virtual void postvisit(int node) = 0;
};

class MultiNodeVisitor : public NodeVisitor {
 private:
  std::vector<NodeVisitor*> observers;

 public:
  MultiNodeVisitor(Graph *g):NodeVisitor(g) {}
  virtual void previsit(int node) {
    for_each(observers.begin(), observers.end(),
	     [node](NodeVisitor *visitor) {
	       visitor->previsit(node);
	     });
  }

  virtual void postvisit(int node) {
    for_each(observers.begin(), observers.end(),
	     [node](NodeVisitor *visitor) {
	       visitor->postvisit(node);
	     });
  }

  void addVisitor(NodeVisitor *v) {
    // assert(v->graph == this->graph);
    observers.push_back(v);
  }
};

class PrePostVisitor : public NodeVisitor {
 private:
  int curr;
  std::vector<int> pre;
  std::vector<int> post;

 public:
  PrePostVisitor(Graph *g):NodeVisitor(g) {
    int num_nodes = g->getNumNodes();
    curr = 0;
    pre.resize(num_nodes);
    post.resize(num_nodes);
  }
  
  void previsit(int node) {
    pre[node] = curr++;
  }

  void postvisit(int node) {
    post[node] = curr++;
  }

  void dump() {
    print_seq(pre);
    print_seq(post);
  }
};

#endif
