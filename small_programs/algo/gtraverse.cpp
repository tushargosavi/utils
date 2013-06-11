#include <vector>
#include <queue>
#include <stack>

#include <gtraverse.h>

DfsSearch::DfsSearch(Graph *g):GraphSearch(g) {
  visited.resize(g->getNumNodes());
}
  
void DfsSearch::search_from(int node) {
  visited[node] = true;
  if (visitor)
    visitor->previsit(node);
  order.push_back(node);
  auto neighbours = graph->neighbours(node);
  std::for_each(neighbours.begin(), neighbours.end(), [this](int &n) {
      if (!visited[n])
	search_from(n);
    });
  if(visitor)
    visitor->postvisit(node);
}

void DfsSearch::search_from_iter(int node) {
  std::stack<int> nodestack;
  visited[node] = true;
  nodestack.push(node);
  while (!nodestack.empty()) {
    int curr = nodestack.top();
    order.push_back(curr);
    visited[curr] = true;
    nodestack.pop();
    auto neighbours = graph->neighbours(curr);
    for(auto iter = neighbours.begin();
	iter != neighbours.end();
	++iter) {
      if (!visited[*iter])
	nodestack.push(*iter);
    }
  }
}

BfsSearch::BfsSearch(Graph *g):GraphSearch(g) {
  visited.resize(g->getNumNodes());
}

void BfsSearch::search_from(int node) {
  visited[node] = true;
  queue.push(node);
  visited[node] = true;
  while(!queue.empty()) {
    int curr = queue.front();
    queue.pop();
    order.push_back(curr);
    auto neighbours = graph->neighbours(curr);
    for(auto iter = neighbours.begin();
	iter != neighbours.end();
	++iter)
      if(!visited[*iter]) {
	visited[*iter] = true;
	queue.push(*iter);
      }
  }
}
