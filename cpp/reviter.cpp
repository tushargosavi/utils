#include <iostream>
#include <vector>
#include <algorithm>
#include <sequtils.h>
#include <deque>

using namespace std;

void print(int t)
{
  cout << t << " ";
}

int main(int argc, char *argv[])
{
  deque<int> c1;

  populate_lseq(c1, 10);
  deque<int>::iterator pos1 = find(c1.begin(), c1.end(), 2);
  deque<int>::iterator pos2 = find(pos1, c1.end(), 7);
  print(*pos1); print(*pos2); cout << endl;
  for_each(pos1, pos2, print);
  cout << endl;

  deque<int>::reverse_iterator rpos1(pos1);
  deque<int>::reverse_iterator rpos2(pos2);
  print(*rpos1); print(*rpos2); cout << endl;
  for_each(rpos2, rpos1, print);
  cout << endl;

  return 0;
}
