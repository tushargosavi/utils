#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum bean_color {
  BROWN,
  GREEN,
  CLEAR
};

char c[] = "BGC";
int bucket[3][3];

int perms[][3] = {
	{ GREEN, CLEAR, BROWN },
	{ GREEN, BROWN, CLEAR },
	{ CLEAR, GREEN, BROWN },
	{ CLEAR, BROWN, GREEN },
	{ BROWN, GREEN, CLEAR },
	{ BROWN, CLEAR, GREEN }
};

/*
 * The 0th bucket will contain type a of beans
 * 1st bucket will contain type b of beans
 * 2nd bucket will contain type c of beans
 */

int total_cost(int a, int b, int c)
{
  int cost = 0;
  cost += bucket[1][a] + bucket[2][a];
  cost += bucket[0][b] + bucket[2][b];
  cost += bucket[0][c] +  bucket[1][c];
  return cost;
}

void process_data(int *in)
{
  int list[] = { 0, 1, 2};
  int temp[3];
  int i =0;
  int cost;
  int min_cost = 0x7FFFFFFF;
  int min[3];

  bucket[0][0] = in[0]; bucket[0][1] = in[1]; bucket[0][2] = in[2];
  bucket[1][0] = in[3]; bucket[1][1] = in[4]; bucket[1][2] = in[5];
  bucket[2][0] = in[6]; bucket[2][1] = in[7]; bucket[2][2] = in[8];

  for (i=0; i<6; i++) {
    memcpy((char*)temp, (char*)list, sizeof(int) * 3);
    cost = total_cost(perms[i][0], perms[i][1], perms[i][2]);
    if (cost <= min_cost) {
      min_cost = cost;
      min[0] = perms[i][0]; min[1] = perms[i][1]; min[2] = perms[i][2];
    }
  }

  printf("%c%c%c %d\n", c[min[0]], c[min[1]], c[min[2]], min_cost);
}

int main()
{
  int in[9];
  int temp[9];
  int i,j;

  while (scanf("%d %d %d %d %d %d %d %d %d", &in[0], &in[1], &in[2],
	    &in[3], &in[4], &in[5], &in[6], &in[7], &in[8]) != EOF) {
    process_data(in);
  }

  return 0;
}
