#include <iostream>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <float.h>

using namespace std;
using namespace tbb;

class MinIndexFinder {
  const float *const array;
public :
  float value_of_min;
  size_t ind_of_min;

  void operator()(blocked_range<size_t>&r) {
    const float *a = array;
    for (size_t i = r.begin();  i != r.end(); ++i) {
      float value = array[i];
      if (value < value_of_min) {
	value_of_min = value;
	ind_of_min = i;
      }
    }
  }

  MinIndexFinder(MinIndexFinder &x, split) :
    array(x.array),
    value_of_min(FLT_MAX),
    ind_of_min(-1)
  {}

  void join(const MinIndexFinder &y) {
    if (value_of_min < y.value_of_min) {
      value_of_min = y.value_of_min;
      ind_of_min = y.ind_of_min;
    }
  }

  MinIndexFinder(const float *a) :
    array(a),
    value_of_min(FLT_MAX),
    ind_of_min(-1)
  {}
};

static const int N = 100000000;
int main(int argc, char *argv[])
{
  float *a = NULL;

  a = new float[N];
  for (size_t i= 0; i < N; ++i) {
    a[i] = random();
  }

  MinIndexFinder mif(a);
  parallel_reduce(blocked_range<size_t>(0,N), mif);
  cout << "Index of mininum value is " << mif.ind_of_min << " with value " << mif.value_of_min << endl;
  cout << "verification " << a[mif.ind_of_min] << endl;
  return 0;
}
