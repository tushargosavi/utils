#include <iostream>
#include <list>
#include <sequtils.h>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
  list<int> lst1;
  list<int> lst2;

  populate_rand(lst1, 10, 100);
  populate_rand(lst2, 10, 100);
  
  print_seq(lst1, "lst1 : ");
  print_seq(lst2, "lst2 : ");

  lst1.splice(lst1.begin(), lst2);
  print_seq(lst1, "lst1 : ");
  print_seq(lst2, "lst2 : ");

  return 0;
}
