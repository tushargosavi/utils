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
  
  reverse(v1.begin(), v1.end());
  print_seq(v1);

  reverse(v1.begin() + 1, v1.end() - 1);
  print_seq(v1);

  return 0;
}
