#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <sequtils.h>

using namespace std;

void print(int elem)
{
  cout << elem << ' ';
}

int square(int x) { return x * x; }

int main(int argc, char *argv[])
{
  vector<int> col;
  set<int> v;

  cout << "For each testing " << endl;
  for (int i=0; i < 10; i++)
    col.push_back(i);
  for_each(col.begin(), col.end(), print);
  cout << endl;

  cout << "transform testing " << endl;
  transform(col.begin(), col.end(),
	    inserter(v, v.end()),
	    square);
  print_seq(v, "after\t");

  col.erase(col.begin(), col.end());
  v.erase(v.begin(), v.end());

  list<int> lst;
  for(int i=24; i <= 30; i++) lst.push_back(i);
  print_seq(lst, "list\t");
  list<int>::iterator pos;
  pos = find_if (lst.begin(), lst.end(),
		 [](int x) {
		   int i = 2;
		   while (i < x / 2) {
		     if ((x % i) == 0) return false;
		     ++i;
		   }
		   return true;
		 });
  if (pos != lst.end()) {
    cout << "prime number found " << *pos << endl;
  } else {
    cout << "No prime found in the given range " << endl;
  }
  return 0;
}
