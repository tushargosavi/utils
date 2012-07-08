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
  vector<int> v2;
  populate_lseq(v1, 1, 5);
  populate_lseq(v1, 1, 5);
  vector<int>::iterator pos = v1.begin();
  advance(pos, 1);
  vector<int>::iterator pos1 = find(pos, v1.end(), 1);

  merge(v1.begin(), pos1,
	pos1, v1.end(),
	back_inserter(v2));
  print_seq(v2);
  return 0;
}
