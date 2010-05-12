/*
  This program is accepted by Online Judge :)
*/

#include <stdio.h>
#include <stdlib.h>

int cycle_len(int i)
{
  int n, count;
  count = 1;
  n = i;
  while (n != 1) {
    /* If n is odd then n <- 3n + 1 else n <- n /2 */
    if (n & 0x1) 
      n = n * 3 + 1;
    else 
      n =  n >> 1;

    count ++;
  }
  return count;
}

void process_data(int i, int j)
{
  int n;
  int start, end;
  int len, max_len;


  if (i <= j) { start = i; end = j; }
  else { start=j ; end = i ; }

  max_len = 0; 
  for( n=start; n <= end; n++) {
    len = cycle_len(n);
    if (max_len < len) max_len = len;
  }
  printf("%d %d %d\n", i, j, max_len);
}

int main()
{
  int i, j;

  while (scanf("%d %d", &i, &j) != EOF) {
    process_data(i, j);
  }

  return 0;
}
