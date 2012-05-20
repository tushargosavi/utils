#include <iostream>
#include <set>
#include <algorithm>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  typedef multiset<int, greater<int> > IntSet;
  int arr[] = { 4, 3, 5, 1, 6, 2, 5};
  IntSet col(&arr[0], arr + sizeof(arr) / sizeof(arr[0]));
  print_seq(col);

  // Isert 4 again
  IntSet::iterator ipos = col.insert(4);
  cout << "4 inserted as element "
       << distance(col.begin(), ipos) + 1
       << endl;

  multiset<int> col2(col.begin(), col.end());
  print_seq(col2, "col2 ");

  col2.erase(col2.begin(), col2.find(3));
  
  int num;
  num = col2.erase(5);
  cout << num << " elements removed " << endl;
  
  print_seq(col2);

  return 0;
}
