#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cmath>
#include <iterator>
#include <sequtils.h>

using namespace std;

template <class T1, class T2>
struct fopow : public std::binary_function<T1,T2,T1>
{
  T1 operator() (T1 base, T1 exp) const {
    return std::pow(base,exp);
  }
};

int main(int argc, char *argv[])
{
  vector<int> col1;
  populate_lseq(col1, 9);
  

  transform(col1.begin(), col1.end(),
	    ostream_iterator<int>(cout, " "),
	    bind1st(fopow<float, int>(), 3));
  cout << endl;
  
  transform(col1.begin(), col1.end(),
	    ostream_iterator<int>(cout, " "),
	    bind2nd(fopow<float, int>(), 3));

  cout << std::endl;

  return 0;
}
