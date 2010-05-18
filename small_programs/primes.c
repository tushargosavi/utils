#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BMAP_SIZE    (1000000000)
unsigned char bmap[(MAX_BMAP_SIZE / 8) + 1];

#define SET_BIT(n) (bmap[n >> 3] |= (1 << (n & 7)))
#define GET_BIT(n) (bmap[n >> 3] & (1 << (n & 7)))

int main(int argc, char **argv)
{
	unsigned int num = 0;
	unsigned int count = 0;
	int BMAP_SIZE = 0;
	int loop_count = 0;

	if (argc == 2)
		BMAP_SIZE = atoi(argv[1]);
	else
		BMAP_SIZE = 10000;

	num = 2;
	loop_count = ceil(sqrt(BMAP_SIZE));
	while (num < loop_count) {
		for (count = 2 * num; count < BMAP_SIZE; count += num)
			SET_BIT(count);

		/* select next element */
		for (num++; num < BMAP_SIZE && GET_BIT(num); num++);
	}

	num = 1;
	while (num < BMAP_SIZE) {
		if (! GET_BIT(num))
			printf("%d ", num);
		num++;
	}
	printf("\n");
	return 0;
}
