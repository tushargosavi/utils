#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> v1;
  
  populate_lseq(v1, 1, 9);
  print_seq(v1, "v1 : ");
  
  rotate(v1.begin(),
	 v1.begin() + 1,
	 v1.end());
  print_seq(v1, "v1 : ");

  rotate(v1.begin(),
	 v1.end() - 2,
	 v1.end());
  print_seq(v1, "v1 : ");

  rotate(v1.begin(),
	 find(v1.begin(), v1.end(), 4),
	 v1.end());
  print_seq(v1, "v1 : ");

  set<int> s1;
  populate_lseq(s1, 1, 9);
  print_seq(s1, "s1 : ");
  
  set<int>::iterator pos = s1.begin();
  advance(pos, 1);
  rotate_copy(s1.begin(),
	      pos,
	      s1.end(),
	      ostream_iterator<int>(cout, " "));
  cout << endl;

  pos = s1.end();
  advance(pos, -2);
  rotate_copy(s1.begin(), pos, s1.end(),
	      ostream_iterator<int>(cout, " "));
  cout << endl;
  
  rotate_copy(s1.begin(), s1.find(4), s1.end(),
	      ostream_iterator<int>(cout, " "));
  cout << endl;
  return 0;
}
