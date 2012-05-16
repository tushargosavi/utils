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

  populate_lseq(col1, 9);
  print_seq(col1);

  return 0;
}
