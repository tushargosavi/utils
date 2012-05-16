#include <iostream>
#include <list>
#include <algorithm>
#include <sequtils.h>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{  
  std::set<int> s;
  populate_lseq(s, 10);
  print_seq(s, "before\t");
  s.erase(3);
  print_seq(s, "after\t");

  cout << "Testing remove on list object " << endl;
  std::list<int> lst;
  for (int i=1; i < 6; i++) {
    lst.push_front(i);
    lst.push_back(i);
  }

  print_seq(lst, "orig");
  lst.erase(remove(lst.begin(), lst.end(), 3),lst.end());
  print_seq(lst, "rm 3");
  lst.remove(4);
  print_seq(lst, "rm 4");
  
  return 0;
}
