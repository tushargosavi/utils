#include <iostream>
#include <vector>
#include <algorithm>
#include <sequtils.h>

using namespace std;

class MeanValue {
private :
  long num;
  long sum;
public :
  MeanValue(): num(0), sum(0) {
  }

  void operator() (int elem) {
    num++;
    sum += elem;
  }

  int numValues() const { return num; }

  double value() {
    return static_cast<double>(sum) / static_cast<double>(num);
  }
};


int main(int argc, char *argv[])
{
  vector<int> v1;

  populate_rand(v1, 10, 100);
  print_seq(v1, "v1 : ");
  MeanValue mv = for_each(v1.begin(), v1.end(),
			  MeanValue());
  cout << "count " << mv.numValues() << "mean " << mv.value() << endl;
  return 0;
}
