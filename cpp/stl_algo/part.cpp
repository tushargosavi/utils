#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

bool isEven(int a) { (a % 2) == 0; }

int main(int argc, char *argv[])
{
  vector<int> v1;

  populate_lseq(v1, 1, 9);
  print_seq(v1, "v1 : ");
  partition(v1.begin(), v1.end(),
	    not1(bind2nd(modulus<int>(), 2)));
  print_seq(v1, "v1 : ");
  return 0;
}
