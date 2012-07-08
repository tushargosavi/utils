#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <deque>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
  deque<int> v1;
  generate_n(back_inserter(v1),
	     10,
	     rand);
  print_seq(v1, "v1 : ");
  return 0;
}
