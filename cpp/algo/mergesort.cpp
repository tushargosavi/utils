#include <iostream>
#include <sequtils.h>

using namespace std;

/*
template<class T>
class vec_slice {
private :
  std::vector<T> slice;
  int start;
  int end;

public:
  vec_slice(std::vector<T> v, int start, int end):start(start), end(end), slice(v) {}
  // change slice parameter.
  T& operator[](int i) {
    return slice[start + i]);
  }
};
*/

void merge(vector<int> &arr, vector<int> &temp,
	   int start, int end)
{
  int mid = (end - start) / 2;
  int i = start;
  int j = mid;
  for(int k = 0; k < (end - start); k++) {
    if ((arr[i] < arr[j]) && i < mid)
      temp[k] = arr[i++];
    else
      temp[k] = arr[j++];
    }
  }
}

void merge_sort(std::vector<int> &arr,
		std::vector<int> &scratch,
		int start, int end)
{
  if (start == end)
    scratch[start] = arr[start];
  mid = (end - start) / 2;
  merge_sort(arr, scratch, start, mid);
  merge_sort(arr, scratch, mid+1, end);
  merge(arr, scratch, start, mid, end);
}

merge_sort(std::vector<int> &arr) {
  std::vector<int> copy;
  copy.resize(arr.size());
  merge_sort(copy, arr, 0, arr.size() - 1);
}

int main(int argc, char **argv)
{
  std::vector<int> arr;
  populate_rand(arr);
  merge_sort(arr);
  print_seq(arr);
  return 0;
}
