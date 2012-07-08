#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <list>
#include <numeric>

using namespace std;

int main(int argc, char *argv[])
{
  list<int> ls1;
  populate_lseq(ls1, 1, 10);
  
  int sum = accumulate(ls1.begin(), ls1.end(), 0);
  cout << "Sum : " << sum << endl;

  int prod = accumulate(ls1.begin(), ls1.end(), 1,
			multiplies<int>());
  cout << "Prod : " << prod << endl;

  vector<int> v1;
  populate_lseq(v1, 1, 6);
  
  cout << "Inner Product ";
  cout << inner_product(v1.begin(), v1.end(),
			v1.begin(),
			0);
  cout << endl;

  cout << "Product of additions :" ;
  cout << inner_product(v1.begin(), v1.end(),
			v1.begin(),
			1,
			multiplies<int>(),
			plus<int>());
  cout << endl;

  cout << "Product of reverser : ";
  cout << inner_product(v1.begin(), v1.end(),
			v1.rbegin(),
			0);
  cout << endl;
  return 0;
}
