#include <iostream>
#include <stdio.h>

using namespace std;

void print_table(int *arr, int rows, int cols) {

}

int knapsack(int* w, int* v, int n, int W) {
  int k[n+1][W+1];
  int max;

  // Initialize the knapsack values
  for(int i = 0; i <= n; i++) k[i][0] = 0;
  for(int i = 0; i <= W; i++) k[0][i] = 0;

  // NOTE
  // i from 1 to n
  //  j from 1 to W
  //    k[i][j] = max{ (k[i-1][j],
  //                    k[i-1][j - w[i-1] + v[i-1]) }
  // In the actual idexes of w and v starts from 1,
  // but we are using c arrays hence indexes starts from 0
  // hence while accessing w and v arrays, we are indexing
  // then as (i-1)
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= W; j++) {

      max = k[i-1][j];

      if ((j - w[i-1]) >= 0) 
	if (max < (k[i-1][j-w[i-1]] + v[i-1]))
	  max = k[i-1][j-w[i-1]] + v[i-1];
      k[i][j] = max;
    }
  }

  return k[n][W];
}

int main(int argc, char **argv)
{
  int count, knapsack_size;
  int *v, *w;

  cin >> count;
  cin >> knapsack_size;
  v = new int[count];
  w = new int[count];
  for(int i = 0; i < count; i++) 
    cin >> v[i];
  for(int i = 0; i < count; i++)
    cin >> w[i];

  int max = knapsack(w, v, count, knapsack_size);
  cout << max << endl;
}
