#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <sequtils.h>

using namespace std;

class Addvalue {
private :
  int theValue;
public :
  Addvalue(int v) : theValue(v) { }

  void operator()(int& elem) {
    elem += theValue;
  }
};

int main(int argc, char *argv[])
{
  vector<int> vec;
  populate_lseq(vec, 20);
  print_seq(vec);

  for_each(vec.begin(), vec.end(), Addvalue(10));
  print_seq(vec);
  return 0;
}
