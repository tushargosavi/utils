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
  populate_lseq(v1, 1, 3);
  print_seq(v1, "one entry  : ");
  
  while (next_permutation(v1.begin(), v1.end())) {
    print_seq(v1, " ");
  }
  print_seq(v1, "afterword : ");
  while(prev_permutation(v1.begin(), v1.end())) {
    print_seq(v1, "v1 : ");
  }
  print_seq(v1, "now : ");
  while(prev_permutation(v1.begin(), v1.end())) {
    print_seq(v1, " ");
  }
  print_seq(v1, "now : ");
  return 0;
}
