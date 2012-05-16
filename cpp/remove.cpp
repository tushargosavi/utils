#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  list<int> col;
  for (int i = 1; i <= 6; ++i) {
    col.push_front(i);
    col.push_back(i);
  }

  print_seq(col, "pre\t");
  list<int>::iterator end = remove(col.begin(), col.end(), 3);
  cout << "Number of removed elements " << distance(end, col.end()) << endl;
  print_seq(col, "rem\t");
  col.erase(end, col.end());
  print_seq(col, "post\t");
  return 0;
}
