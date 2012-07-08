#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_lseq(v1, 2, 6);
  populate_lseq(v1, 4, 9);
  populate_lseq(v1, 1, 7);
  
  print_seq(v1, "v1                : ");

  vector<int>::iterator pos = remove(v1.begin(), v1.end(),
	 5);
  print_seq(v1, "v1 (after remove) : ");

  v1.erase(pos, v1.end());
  print_seq(v1, "v1 (after erase)  : ");

  v1.erase(remove_if(v1.begin(), v1.end(),
		     bind2nd(less<int>(), 4)),
	   v1.end());
  print_seq(v1, "v1 (after <4 )    : ");
		       
  return 0;
}
