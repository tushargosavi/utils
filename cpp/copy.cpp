#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sequtils.h>

using namespace std;

class Test {
private :
  int value;
public :
  Test(int v) : value(v) { cout << "calling constructor with " << v << endl; }
  ~Test() { cout << "destroying " << value << endl; }

  Test(const Test& t) {
    cout << "calling copy constructor obj " << this << " from " <<  &t << endl;
    if (this != &t) {
      value = t.value;
    }
  }

  Test& operator=(const Test& t)
  {
    if (this != &t) {
      value = t.value;
    }
    return *this;
  }
      
  int getValue() const { return value; }
  void set(int v) { value = v; };
};

ostream& operator<<(ostream& os, const Test& t)
{
  os << "[ref " << &t << " value " << t.getValue() << "] " << endl;
  return os;
}

int main(int argc, char *argv[])
{
  list<Test> a;
  list<Test> b;
  Test v(0);

  for(int i = 0; i < 10; ++i) {
    v.set(i);
    a.push_back(v);
  }

  cout << endl;
  cout << "before copying " << endl;
  b = a;
  
  print_seq(a);
  print_seq(b);

  return 0;
}
