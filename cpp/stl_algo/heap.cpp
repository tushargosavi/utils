#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_lseq(v1, 1, 9);
  print_seq(v1);
  random_shuffle(v1.begin(), v1.end());
  print_seq(v1);
  make_heap(v1.begin(), v1.end());
  print_seq(v1);
  return 0;
}
