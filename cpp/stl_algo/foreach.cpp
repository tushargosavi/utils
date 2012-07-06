#include <iostream>
#include <algorithm>
#include <iterator>
#include <sequtils.h>
#include <list>
#include <vector>


using namespace std;

class ProcessElement
{
private :
  int inc;
public :

  ProcessElement() : inc(10) { }
  ProcessElement(int n) : inc(n) { }

  void operator()(int &i) {
    i += inc;
  }
};

int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_lseq(v1,10);
  print_seq(v1);

  for_each(v1.begin(), v1.end(), ProcessElement());
  print_seq(v1);

  for_each(v1.begin(), v1.end(), ProcessElement(-10));
  print_seq(v1);

  list<int> v2;
  populate_rand(v2, 30);
  print_seq(v2);
  cout << "Max Element " << *max_element(v2.begin(), v2.end()) << std::endl;
  cout << "Min Element " << *min_element(v2.begin(), v2.end()) << std::endl;
  
  /* with reverse */
  cout << "Max Element " << *max_element(v2.begin(), v2.end(), less<int>) << std::endl;
  cout << "Min Element " << *min_element(v2.begin(), v2.end(), less<int>) << std::endl;

  return 0;
}
