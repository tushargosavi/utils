#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

class MeanValue {
private:
  int num;
  int sum;
public :
  MeanValue():num(0), sum(0) {
  }

  void operator()(int a) {
    num ++;
    sum += a;
  }

  operator double() {
    return static_cast<double>(sum) / static_cast<double>(num);
  }
};

int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_rand(v1, 10, 100);
  print_seq(v1);
  double mean = for_each(v1.begin(), v1.end(),
		       MeanValue());
  cout << "Mean value is : " << mean << std::endl;
  return 0;
}
