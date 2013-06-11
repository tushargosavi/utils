#include <stdlib.h>
#include <iostream>
#include <graph.h>
#include <gtraverse.h>

extern void displayGraph(const char *str);

int main(int argc, char **argv)
{
  int startnode = 0;
  if (argc >= 2) {
    startnode = atoi(argv[1]);
  }
  DiGraph *g = new DiGraph(12);
  g->readFromFile("g.graph");
  PrePostVisitor *v = new PrePostVisitor(g);
  Graph *rev = reverseGraph(g);
  DfsSearch search(rev);
  search.setVisitor(v);
  search.search_from(startnode);
  search.print_order();
  v->dump();
  delete v;
  delete g;
  return 0;
}
