#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sequtils.h>

using namespace std;


int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_rand(v1, 10);
  
  print_seq(v1);
  iter_swap(v1.begin(), ++v1.begin());
  print_seq(v1);
  
  iter_swap(v1.begin(), --v1.end());
  print_seq(v1);
  return 0;
}
