#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include <sequtils.h>
#include <countptr.h>

using namespace std;

ostream& operator<<(ostream& os, const CountedPtr<int>& elem) {
  os << *elem << ' ';
  return os;
}

int main(int argc, char *argv[])
{
  static int v[]= {3,5,9,1,6,4};
  typedef CountedPtr<int> IntPtr;

  deque<IntPtr> col1;
  list<IntPtr> col2;
  
  for (int i =0 ; i < (sizeof(v) / sizeof(v[0])); ++i) {
    IntPtr ptr(new int(v[i]));
    col1.push_back(ptr);
    col2.push_front(ptr);
  }

  print_seq(col1);
  print_seq(col2);

  // square 3rd element
  *col1[2] *= *col1[2];
  // negate first element
  (**col1.begin()) *= -1;
  (**col2.begin()) = 0;

  print_seq(col1);
  print_seq(col2);

  return 0;
}
