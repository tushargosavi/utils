#include <iostream>
#include <stdio.h>
#include <string>
#include <limits.h>

using namespace std;

int get_cost(int *dim, int num) {
  int c[num][num];
  int min, cost;


  for(int i = 0; i < num; i++)
    c[i][i] = 0;


  for(int i =0; i < num; i++) {
    for(int j = 0; j < num; j++) 
      printf("%12d", c[i][j]);
    printf("\n");
  }
  
  for(int s = 0; s < num; s++) {
    for(int i = 0; i < num - s; i++) {
      min = 0x7fffffff;
      int j = i + s;
      for(int k = i; k < j; k++)  {
	printf(" i %d k %d j %d  (%d %d) (%d x %d x %d)\n", i, k, j, c[i][k], c[k+1][j], dim[i], dim[k+1], dim[j+1]);
	cost = c[i][k] + c[k+1][j] + (dim[i] * dim[k+1] * dim[j+1]);
	if (cost < min) {
	  min = cost;
	  c[i][j] = min;
	}
      }
    }
  }

  for(int i =0; i < num; i++) {
    for(int j = 0; j < num; j++) 
      printf("%12d", c[i][j]);
    printf("\n");
  }

  return c[0][num-1];
}

int main() {
  int num;
  int *dim;

  cin >> num;
  dim = new int[num+1];
  for(int i = 0; i <= num; i++) 
    cin >> dim[i];

  for(int i = 0; i < num+1; i++) cout << dim[i] << " ";
  cout << endl;
  int cost = get_cost(dim, num);
  cout << cost << endl;
  return 0;
}
  
