#include <iostream>
#include <set>
#include <algorithm>
#include <sequtils.h>

using namespace std;

template<typename T>
class RuntimeCmp {
public :
  enum cmp_mode { normal, reverse };
private :
  cmp_mode mode;
public :
  RuntimeCmp(cmp_mode m = normal): mode(m) {}
  bool operator()(const T &t1, const T &t2) const {
    return mode == normal ? t1 < t2 : t2 < t1;
  }
  bool operator == (const RuntimeCmp& rc) {
    return mode == rc.mode;
  }
};

typedef set<int, RuntimeCmp<int> > IntSet;

int main(int argc, char *argv[])
{
  IntSet s;

  random_init();
  populate_rand(s, 10, 20);
  print_seq(s);

  RuntimeCmp<int> reverse_order(RuntimeCmp<int>::reverse);
  IntSet s2(reverse_order);
  populate_rand(s2, 10, 20);
  print_seq(s2);

  s = s2;
  s.insert(3);
  print_seq(s, "s :");
  print_seq(s2, "s2 :");

  if (s.value_comp() == s2.value_comp()) {
    cout << "s and s2 have same coparation criteria"
	 << endl;
  } else {
    cout << "s and s2 have different comparation criteria"
	 << endl;
  }

  return 0;
}
