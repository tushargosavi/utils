#include <iostream>
#include <set>
#include <algorithm>
#include <sequtils.h>
using namespace std;

int main(int argc, char *argv[])
{
  typedef set<int, greater<int> > IntSet;

  IntSet col;

  col.insert(4);
  col.insert(3);
  col.insert(5);
  col.insert(1);
  col.insert(6);
  col.insert(2);
  col.insert(5);

  IntSet::iterator pos;
  for (pos = col.begin(); pos != col.end() ; ++pos) {
    cout << *pos << ' ';
  }
  cout << endl;

  pair<IntSet::iterator , bool> status = col.insert(4);
  if (status.second) {
    cout << "4 inserted as element"
	 << distance(col.begin(), status.first) + 1
	 << endl;
  } else {
    cout << "4 already exists" << endl;
  }

  set<int> col2(col.begin(), col.end());
  print_seq(col2);

  col2.erase(col2.begin(), col2.find(3));
  
  int num;
  num = col2.erase(5);
  cout << num << "elements removed " << endl;

  print_seq(col2);
  cout << endl;
  return 0;
}
