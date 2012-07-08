#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  int c1[] = { 1, 2, 2, 4, 6, 7, 7, 9 };
  int num1 = sizeof(c1) / sizeof(c1[0]);

  int c2[] = { 2, 2, 2, 3, 6, 6, 8, 9 };
  int num2 = sizeof(c2) / sizeof(c2[0]);

  cout << "c1    : ";
  copy(c1, c1 + num1,
       ostream_iterator<int>(cout, " "));
  cout << endl;
  cout << "c2    : ";
  copy(c2, c2 + num2,
       ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "Merge : ";
  merge(c1, c1 + num1,
	c2, c2 + num2,
	ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "Set   : ";
  set_union(c1, c1+num1,
	    c2, c2+num2,
	    ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "Set Int : ";
  set_intersection(c1, c1+num1,
		   c2, c2+num2,
		   ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "Set Diff : ";
  set_difference(c1, c1+num1,
		 c2, c2+num2,
		 ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "SetSDiff : ";
  set_symmetric_difference(c1, c1+num1,
		 c2, c2+num2,
		 ostream_iterator<int>(cout, " "));
  cout << endl;
  
  return 0;
}
