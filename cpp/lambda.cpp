#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> vec;
  int inc = 10;
  populate_lseq(vec, 20);
  print_seq(vec);

  for_each(vec.begin(), vec.end(),
	   [](int& elem) {
	     elem += 10;
	   });
  print_seq(vec);
  return 0;
}
