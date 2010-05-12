#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS   50
#define MAX_DIAMENTION 20

int mat[MAX_ELEMENTS][MAX_DIAMENTION];
int dep_mat[MAX_ELEMENTS][MAX_ELEMENTS];

enum compare_result {
  LESS_THAN = 1,
  GT_THAN,
  NO_COMPARE
};

/*
 * compare the vectors
 */
int cmp_vec(int *src, int *dest, int n)
{
  int i =0;
  for (i=0; i<n; i++) if (!(src[i] < dest[i])) break;
  if (i== n) return LESS_THAN; 
  
  for (i=0; i<n; i++) if (!(src[i] > dest[i])) break;
  if (i== n) return GT_THAN;
  
  return NO_COMPARE;	
}

/*
 * sort a list of integers using bubble sort
 */
void sort(int *in, int n)
{
  int i=0, j =0;
  int temp;
  
  for (i=0; i < n; i++) {
    for (j= i+1; j < n ; j++) {
      if (in[i] > in[j]) {
	temp = in[i];
	in[i] = in[j];
	in[j] = temp;
      }
    }
  }
}

/*
 * This is used to read the matrix from stdin
 */
void read_matrix(int num, int dia)
{
  int i =0;
  int j =0;
  for (i =0 ; i < num; i++)
    for (j=0; j < dia; j++) 
      scanf("%d", &mat[i][j]);
}

void print_matrix(int num, int dia)
{
  int i, j;
  for (i=0; i < num; i++) {
    for (j=0; j < dia; j++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }
}

void print_dep_matrix(int num)
{
  int i, j;
  for (i=0; i < num; i++) {
    for (j=0; j < num; j++)
      printf("%d ", dep_mat[i][j]);
    printf("\n");
  }
}

/*
 * We will start searching from node, which does not have
 * any node smaller than it. If any node is smaller than
 * the node we have selected then the lengh won't be the optimal.
 * as the longest chain will contain the smaller node too.
 */
int start_node(int *v, int num)
{
  int i,j;
  int min = -1;
  int count =0;
  int node;

  node = -1;
  for (i=0; i < num; i++) {
    count = 0;
    for (j=0; j< num; j++) {
      count += dep_mat[j][i];
    }
    if (count == 0 && !v[i]) {
      node = i;
    }
  }
  return node;
}

/* 
 * Does a depth first searching on generated graph, keep count of
 * level, and if we have gone deeper then save the state.
 */
int max_list[MAX_ELEMENTS];
void start_at_node(int node, int num, int count, int *list, int *max)
{
  int j;
  int i;

  list[count++] = node;
  for (j=0; j < num; j++) {
    if (dep_mat[node][j] == 1 && j!= node) { 
      start_at_node(j, num, count, list, max);
    }
  }
  if (count > *max) {
    *max = count;
    memcpy(max_list, list, sizeof(int) * count);
  }
}

/*
 * For each starting point, do depth first search
 */
void longest_path(int num)
{
  int node;
  int visited[MAX_ELEMENTS];
  int max = 0;
  int list[MAX_ELEMENTS];
  int i = 0;

  memset(visited, 0, sizeof(int) * MAX_ELEMENTS);
  while ((node = start_node(visited, num)) != -1 ) {
    visited[node] =1;
    start_at_node(node, num, 0, list, &max);
  }
  printf("%d\n", max);
  for (i=0; i < max-1; i++) 
    printf("%d ", max_list[i] + 1);
  printf("%d\n", max_list[i] + 1);
}


void process_matrix(num, dia)
{
  int i =0;
  int j =0;

  /* First sort, for faster comparison */
  for (i=0 ; i < num; i++) 
    sort(&(mat[i][0]), dia);

  /* generate a dependenty matrix, this is same as graph
   * representation.
   * If element [i][j] is set then i <= j.
   */
  for (i=0; i< num; i++) {
    for(j =0; j < num; j++) {
      dep_mat[i][j] = 0;
      if (cmp_vec(&(mat[i][0]), &(mat[j][0]), dia) == LESS_THAN)
	dep_mat[i][j] = 1;
    }
  }

  /* Do depth first search to find longest paths */
  longest_path(num); 
}


    
int main()
{
  int num, dia;

  while (scanf("%d %d", &num, &dia) != EOF) {
    read_matrix(num, dia);
    process_matrix(num, dia);
  }
  return 0;
}

