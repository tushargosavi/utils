#include <iostream>
#include <algorithm>
#include <carray.h>
#include <functional>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  carray<int, 10> a;
  for (unsigned int i=0; i <a.size(); ++i) {
    a[i] = i + 1;
  }
  print_seq(a);
  
  reverse(a.begin(), a.end());
  print_seq(a);

  transform(a.begin(), a.end(),
	    a.begin(),
	    negate<int>());
  print_seq(a);
  return 0;
}
