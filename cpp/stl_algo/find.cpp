#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_lseq(v1, 1, 10);
  populate_lseq(v1, 1, 10);
  print_seq(v1);

  vector<int>::iterator pos1 = find(v1.begin(), v1.end(), 4);
  vector<int>::iterator pos2 = find(++pos1, v1.end(), 4);
  
  copy(--pos1, ++pos2,
       ostream_iterator<int>(cout, " "));
  cout << endl;

  print_seq(v1);
  transform(v1.begin(), v1.end(),
	    v1.begin(),
	    v1.begin(),
	    multiplies<int>());
  print_seq(v1);

  transform(v1.begin(), v1.end(),
	    ostream_iterator<int>(cout, " "),
	    negate<int>());
  cout << std::endl;
  print_seq(v1);
  return 0;
}
