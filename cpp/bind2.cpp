#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <deque>
#include <set>

#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  set<int, greater<int> > col1;
  deque<int> col2;
  set<int> st;
  vector<int> v;

  populate_lseq(col1, 9);
  print_seq(col1);

  transform(col1.begin(), col1.end(),
	    back_inserter(col2),
	    bind2nd(multiplies<int>(), 10));

  print_seq(col2);

  transform(col2.begin(), col2.end(),
	   col2.begin(),
	   col2.begin(),
	   multiplies<int>());
  print_seq(col2, "sq:");

  transform(col2.begin(), col2.end(),
	    back_inserter(v),
	    [](int x) {
	      return x * x;
	    });

  col2.erase(col2.begin(), col2.end());
  populate_lseq(col2, 24, 60);
  print_seq(col2, "col2");
  replace_if (col2.begin(), col2.end(),
	      bind2nd(equal_to<int>(), 50),
	      42);
  print_seq(col2, "rpl");

  col2.erase(remove_if(col2.begin(), col2.end(),
		       bind2nd(less<int>(), 50)),
	     col2.end());
  print_seq(col2, "rm");
  return 0;
}
