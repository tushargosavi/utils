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
  
  populate_lseq(v1, 1, 7);
  populate_lseq(v1, 1, 9);
  vector<int>::iterator pos = find(v1.begin(), v1.end(), 7);
  pos ++;
  inplace_merge(v1.begin(), pos, v1.end());
  print_seq(v1);

  return 0;
}
