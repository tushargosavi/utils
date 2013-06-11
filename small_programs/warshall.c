#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INT		(0x0FFFFFFF)
struct graph {
  int nodes;
  int a[100][100];
};

void print_graph(struct graph *g)
{
  int i, j;
  int n = g->nodes;
  for (i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      if (g->a[i][j] == MAX_INT) printf("   ");
      else printf("%02d ", g->a[i][j]);
    }
    printf("\n");
  }
}

/*
 * Read graph.
 * Graph is stored in a file like
 * <digit>  number of nodes.
 * <digit> <number of edges> <edge1> <weight1> .... <edgen> <weightn>
 * ..
 */
struct graph *read_graph()
{
  int n;
  int edges;
  int i,j;
  struct graph *g;
  int node, weight;

  g = (struct graph*)malloc(sizeof(struct graph));
  memset(g, 0, sizeof(struct graph));

  scanf("%d", &n);
  g->nodes = n;

  for(i=0;i<n; i++) {
    for (j=0; j < n; j++) {
      g->a[i][j] = MAX_INT;
    }
    g->a[i][i] = 0;
  }

  for (i=0; i < n ; i++) {
    scanf("%d", &edges);
    for(j = 0; j < edges; j++)  {
      scanf("%d %d", &node, &weight);
      g->a[i][node] = weight;
    }
  }
  return g;
}

#define min(a,b) (a>b? b : a)

void shortest_path(struct graph *g)
{
  int i,j,k;
  int n = g->nodes;

  for (k = 0; k < n; k++) 
    for (i=0; i < n; i++)
      for(j = 0; j < n; j++) 
	g->a[i][j] = min(g->a[i][j], 
			 g->a[i][k] + g->a[k][j]);
}

int main()
{
  struct graph *g;
  g = read_graph();
  print_graph(g);
  printf("==========================\n");
  shortest_path(g);
  print_graph(g);
}
