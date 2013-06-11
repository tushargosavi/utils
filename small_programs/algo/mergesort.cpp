#include <iostream>
#include <vector>
#include <sequtils.h>

using namespace std;

typedef std::vector<int> ivarr;

ivarr merge(ivarr &a, ivarr b)
{
  ivarr c;
  auto aiter = a.begin();
  auto biter = b.begin();
  while(true) {
    if (*aiter < *biter)
      c.push_back(*aiter++);
    else
      c.push_back(*biter++);
    if (aiter == a.end()) {
      std::copy(biter, b.end(), back_inserter(c));
      break;
    }
    if (biter == b.end()) {
      std::copy(aiter, a.end(), back_inserter(c));
      break;
    }
  }
  return c;
}

ivarr mergesort(ivarr &t)
{
  /* base condition, if array of size 1 then return the
     same array */
  if (t.size() == 1) return t;

  ivarr a;
  ivarr b;
  auto mid = t.begin() + (t.size() / 2); // middle iterator.
  std::copy(t.begin(), mid, back_inserter(a));
  std::copy(mid, t.end(), back_inserter(b));
  
  a = mergesort(a);
  b = mergesort(b);
  return merge(a,b);
}


int main(int argc, char **argv)
{
  ivarr v;
  populate_rand(v, 10);
  print_seq(v);
  ivarr sv = mergesort(v);
  print_seq(sv);
  return 0;
}
