#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <cstdlib>

using namespace std;

int isEven(int n) {
  return (n % 2 == 0);
}

int main(int argc, char *argv[])
{
  vector<int> v1;
  int num;

  populate_lseq(v1, 1, 10);
  print_seq(v1);
  
  num = count(v1.begin(), v1.end(), 4);
  cout << "Number of element equal to 4 is : " << num << std::endl;

  num = count_if(v1.begin(), v1.end(), isEven);
  cout << "Number of even number in list is : " << num << std::endl;

  // number of element greater than 4.
  num = count_if(v1.begin(), v1.end(),
		 bind2nd(greater<int>(), 4));
  cout << "Number of element greater than 4 are " << num << std::endl;

  int min = *min_element(v1.begin(), v1.end());
  int max = *min_element(v1.begin(), v1.end(), greater<int>());
  cout << "Min " << min << std::endl;
  cout << "Max " << max << std::endl;
  return 0;
}
