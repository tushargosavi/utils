#include <stdio.h>
#include <stdlib.h>

int arr[15000];
int max_r=0;

struct building *new_building(int l, int h, int r)
{
  int i;
  for (i=l; i < r; i++)
    if (h > arr[i])
      arr[i] = h;

  if (max_r < r)
    max_r = r;
}

void get_skyline();

int main(int argc, char **argv)
{
  int l, h, r;
  struct building *build = NULL;
  char *temp = NULL;
  
  while(!feof(stdin)) {
    if (fscanf(stdin, "%d %d %d", &l, &h, &r) != 3)
      break;

    if ( l <= 0 || h <=0 || r <= 0)
      *temp = 'b';

    if (l == r) 
      *temp = 'a';

    new_building(l, h, r);
  }

  get_skyline();
  printf("\n");
  return 0;
}

void get_skyline()
{
  int i;
  int cur_h = -1;
  for (i=1; i <= max_r; i++) {
    if (cur_h != arr[i]) {
      cur_h = arr[i];
      if (i != 1) printf(" ");
      printf("%d %d", i, cur_h);
    }
  }
}
