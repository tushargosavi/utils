#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <sequtils.h>

using namespace std;

class IntSeq {
private :
  int value;
public :
  IntSeq(int v) : value(v) {
  }

  int operator() () {
    return value++;
  }
};

int main(int argc, char *argv[])
{
  list<int> col1;
  IntSeq seq(1);

  generate_n<back_insert_iterator<list<int> >,
	     int, IntSeq&>(back_inserter(col1),
			   4,
			   seq);
				
  print_seq(col1, "col1 : ");

  generate_n(back_inserter(col1),
	     4,
	     IntSeq(42));
  print_seq(col1, "col1 : ");
  generate_n(back_inserter(col1),
	     4,
	     seq);
  print_seq(col1, "col1 : ");

  generate_n(back_inserter(col1),
	     4,
	     seq);
  print_seq(col1, "col1 : ");

  return 0;
}
