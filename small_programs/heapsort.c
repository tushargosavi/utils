#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT_IDX(idx)	(idx << 1)
#define RIGHT_IDX(idx)  (idx << 1 | 1)

void print_array(int *arr, int n)
{
	int i = 0;
	for(i=1; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

/* This function fix the relation between
 * node and subtree of a node.
 */
void heapify(int *arr, int idx, int len)
{
	int left, right, large, temp;

	left = LEFT_IDX(idx);
	right = RIGHT_IDX(idx);
	if (left <= len && arr[left] > arr[idx])
		large = left;
	else
		large = idx;
	if (right <= len && arr[right] > arr[large])
		large = right;

	if (large != idx) {
		temp = arr[idx];
		arr[idx] = arr[large];
		arr[large] = temp;
		heapify(arr, large, len);
	}
}

/*
 * The n/2 nodes are at leaves they are heap of size 1
 * We build a heap, we start from n/2 to 1 adding element
 * to already established heap.
 */
int create_max_heap(int *arr, int n)
{
	int i = n /2;
	while (i >= 1) {
		heapify(arr, i, n);
		i = i - 1;
	}
}

int heapsort(int *arr, int sz)
{
	int temp;
	int n;

	create_max_heap(arr, sz);
	n = sz;
	while (n >= 2) {
		temp = arr[1];
		arr[1] = arr[n];
		arr[n] = temp;
		n--;
		heapify(arr, 1, n);
	}
}

int main(int argc, char **argv)
{
	int n, i;
	int *arr = (int *)malloc(sizeof(int) * 100);

	scanf("%d", &n);
	arr[0] = 0;
	for (i=0; i < n; i++) {
		scanf("%d", &arr[i+1]);
	}
	heapsort(arr, n);
	printf("\nSorted Array\n");
	print_array(arr, n);
	return 0;
}

