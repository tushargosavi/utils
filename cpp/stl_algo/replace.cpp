#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <list>
using namespace std;

int main(int argc, char *argv[])
{
  list<int> v1;
  populate_lseq(v1, 2, 7);
  populate_lseq(v1, 4, 9);
  print_seq(v1);

  replace_copy(v1.begin(), v1.end(),
	       ostream_iterator<int>(cout, " "),
	       5,
	       55);
  cout << endl;
  replace_copy_if(v1.begin(), v1.end(),
		  ostream_iterator<int>(cout, " "),
		  bind2nd(less<int>(), 5),
		  42);
  cout << endl;
  replace_copy_if(v1.begin(), v1.end(),
		  ostream_iterator<int>(cout, " "),
		  bind2nd(modulus<int>(), 2),
		  0);
  cout << endl;
		
  return 0;
}
