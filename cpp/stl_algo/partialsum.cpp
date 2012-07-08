#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <list>
#include <numeric>

using namespace std;

int main(int argc, char *argv[])
{
  list<int> l1;
  vector<int> v1;

  populate_lseq(l1, 1, 9);
  partial_sum(l1.begin(), l1.end(), back_inserter(v1));

  print_seq(l1);
  print_seq(v1);

  partial_sum(l1.begin(), l1.end(),
	      v1.begin(),
	      multiplies<int>());
  print_seq(v1);

  adjacent_difference(l1.begin(), l1.end(),
		      ostream_iterator<int>(cout, " "));
  cout << endl;
  adjacent_difference(l1.begin(), l1.end(),
		      ostream_iterator<int>(cout, " "),
		      plus<int>());
  cout << endl;
  adjacent_difference(l1.begin(), l1.end(),
		      ostream_iterator<int>(cout, " "),
		      multiplies<int>());
  cout << endl;

		      
  return 0;
}
