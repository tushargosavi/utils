#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <graph.h>
#include <sequtils.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <gtraverse.h>

extern void random_init(void);
extern void displayGraph(const char *);

int main(int argc, char **argv)
{
  random_init();
  Graph *g = makeRandomGraph<Graph>(10, 11);
  g->write_dot_file("/tmp/graph.dot");
  DfsSearch search(g);
  search.search_from(0);
  search.print_order();
  BfsSearch s(g);
  s.search_from(0);
  s.print_order();
  displayGraph("/tmp/graph.dot");
  return 0;
}
