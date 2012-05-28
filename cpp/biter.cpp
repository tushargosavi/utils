#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> col1;
  back_insert_iterator<vector<int> > iter(col1);

  // assigning a value to iterator adds the
  // element in the array

  *iter = 1;
  *iter = 2;
  *iter = 3;

  back_inserter(col1) = 4;
  print_seq(col1);

  cout << "================================ " << endl;
  vector<int> v1;
  vector<int> v2;
  
  populate_lseq(v1, 10);
  v2.push_back(10);
  
  copy(v1.begin(), v1.end(),
       back_inserter(v2));
  print_seq(v1, "v1 : ");
  print_seq(v2, "v2 : ");
  
  cout << "=======================================" << endl;
  ostream_iterator<int> intWriter(cout, "\n");
  *intWriter = 42;
  *intWriter = 10;
  *intWriter = 50;
  copy(v1.begin(), v1.end(),
       ostream_iterator<int>(cout));
  cout << endl;
  copy(v1.begin(), v1.end(),
       ostream_iterator<int>(cout, " < "));
  cout << endl;

  return 0;
}
