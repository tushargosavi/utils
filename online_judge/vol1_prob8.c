#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void non_workers(int , int, int);

int main(int argc, char **argv)
{
  int h0,h;
  int n=0;
  int r = 0;
  int l =0;
  int w = 0;
  int non_workers = 0;

  while (1) {
    scanf("%d %d", &h0, &w);
    if (h0 == 0 && w == 0)
      break;

    for (n = 1; n < 10000000; n++) {
      h = h0;
      l = 0;
      while (h > 1) {
	r = h % (1 + n);
	h = (h / ( 1 + n));
	if (r) break; 
	l ++;
      }
      if (h == 1 && r == 0 && pow(n, l) == w) {
	break;
      }
    }

    non_working(h0, n, l);
  }
}

int non_working(int h0, int n, int l)
{
  int h = h0;
  int total = 1;
  int total_h = h0;
  int cur_prod = 1;
  int cur_height;
  int i=0;

  for (i = 1; i <= l ; i++) {
    cur_prod *= n;
    total += cur_prod;
    h = h / ( 1 + n);
    total_h += h * cur_prod;
  }
  total = total - cur_prod;
  printf("%d %d\n", total, total_h);
}
