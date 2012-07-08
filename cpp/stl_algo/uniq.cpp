#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <list>

using namespace std;

int main(int argc, char *argv[])
{
  int source[] = {
    1,4,4, 6, 1, 2, 2, 3, 1, 6, 6, 6, 5, 7, 5, 4, 4 };
  int sourceNum = sizeof(source) / sizeof(source[0]);
  
  list<int> l1;
  
  copy(source, source + sourceNum,
       back_inserter(l1));
  print_seq(l1, "l1 : ");
  list<int>::iterator pos;
  
  pos = unique(l1.begin(),  l1.end());
  copy(l1.begin(), pos,
       ostream_iterator<int>(cout, " "));
  cout << endl;
  print_seq(l1, "l1 : ");

  /* Reinitialize the sequence */
  copy(source, source + sourceNum,
       l1.begin());
  l1.erase(unique(l1.begin(), l1.end(),
		  greater<int>()),
	   l1.end());
  print_seq(l1, "l1 : ");
  return 0;
}
