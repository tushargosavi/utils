#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <deque>
using namespace std;

int main(int argc, char *argv[])
{
  vector<int> v1;
  deque<int> v2;

  populate_lseq(v1, 1, 10);
  populate_lseq(v2, 11, 23);

  print_seq(v1, "v1 : ");
  print_seq(v2, "v2 : ");

  deque<int>::iterator pos = swap_ranges(v1.begin(), v1.end(),
					 v2.begin());

  print_seq(v1, "v1 : ");
  print_seq(v2, "v2 : ");

  if (pos != v2.end()) {
    cout << "Fist element not modified " << *pos << endl;
  }

  swap_ranges(v2.begin(), v2.begin() + 3,
	      v2.rbegin());
  
  print_seq(v1, "v1 : ");
  print_seq(v2, "v2 : ");

  return 0;
}
