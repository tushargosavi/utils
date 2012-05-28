#include <iostream>
#include <vector>
#include <set>
#include <sequtils.h>
#include <ait.h>

using namespace std;

int main(int argc, char *argv[])
{
  set<int> col1;
  asso_insert_iterator<set<int> > iter(col1);
  
  *iter = 1;
  *iter = 2;
  *iter = 3;
  iter++;
  *iter = 4;

  asso_inserter(col1) = 44;
  asso_inserter(col1) = 55;
  
  print_seq(col1, "col1 : ");
  return 0;
}
