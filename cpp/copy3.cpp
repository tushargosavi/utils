#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;

template<typename T>
void print_sequence(const T &t)
{
  typename T::const_iterator pos;
  for (pos = t.begin(); pos != t.end(); ++pos) {
    cout << *pos << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  list<int> col1;

  for (int i=1 ; i < 9; ++i)
    col1.push_back(i);
  print_sequence(col1);

  vector<int> col2;
  copy(col1.begin(), col1.end(), back_inserter(col2));
  print_sequence(col2);

  deque<int> col3;
  copy(col2.begin(), col2.end(), front_inserter(col3));
  print_sequence(col3);

  set<int> col4;
  copy(col1.begin(), col1.end(), inserter(col4, col4.begin()));
  print_sequence(col4);

  return 0;
}
