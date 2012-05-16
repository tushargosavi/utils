#include <iostream>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
  typedef std::set<int> Intset;

  Intset myset;
  myset.insert(1);
  myset.insert(2);
  myset.insert(3);
  myset.insert(1);
  myset.insert(6);
  myset.insert(10);
  myset.insert(6);

  Intset::const_iterator pos;
  for (pos = myset.begin() ; pos != myset.end(); ++pos) {
    std::cout << *pos << std::endl;
  }

  std::cout << std::endl;

  return 0;
}
