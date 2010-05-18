#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNTRIES  30

float cmat[MAX_COUNTRIES][MAX_COUNTRIES];

void read_conversion_mat(int num)
{
  int i, j;
  for (i=0; i < num ; i++) 
    for (j = 0; j < num ; j++) {
      if (i==j) {
	cmat[i][j] = 1;
      } else {
	scanf("%f", &(cmat[i][j]));
      }
    }
}

void print_conversion_mat(int n)
{
  int i, j;
  for (i=0; i < n; i++) {
    for (j=0; j < n; j++)
      printf("%04.04f ", cmat[i][j]);
    printf("\n");
  }
}

int cur_seq[MAX_COUNTRIES];
int max_seq[MAX_COUNTRIES];
int max_count;
float max_profit;

/* start : Index of starting contry.
 * count : current number of transactions
 * num   : total number of contires
 * prod  : current running product
 */
void get_max_seq(int start, int count, int num, int last, float prod)
{
  int i = 0;
  cur_seq[count] = last;
  if (last == start && prod > max_profit) {
    max_profit = prod;
    max_count = count +1;
    for (i=0; i< max_count; i++) max_seq[i] = cur_seq[i];
  }
  if (count == num-1) return;
  for (i=0; i < num; i++) {
    if (i != last)
      get_max_seq(start, (count +1), num, i, prod * cmat[last][i]);
  }
}

void process_conversion_mat(int num)
{
  int i =0;
  max_profit = 1.0;
  max_count = 0;
  for (i=0; i < num; i++) {
    get_max_seq(i, 0, num, i, 1.0);
  }

  if (max_count != 0) {
    for(i=0; i < max_count -1; i++)
      printf("%d ", max_seq[i] + 1);
    printf("%d\n", max_seq[i] + 1);
  } else {
    printf("no arbitrage sequence exists\n");
  }
}


int main()
{
  int num;

  while (scanf("%d", &num) != EOF) {
    read_conversion_mat(num);
    process_conversion_mat(num);
  }
  return 0;
}
