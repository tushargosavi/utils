#include <iostream>

using namespace std;

class Test {
protected :
  int i;

public :
  /* default constructore */
  Test() {
    cout << "Inside default constructor 0x" << std::hex << this << std::dec << endl;
  }

  /* copy constructor */
  Test(Test &t) {
    cout << "Inside copy constructor " << std::hex << this << " from " << &t << std::dec << endl;
    this->i = t.i;
  }

  ~Test() {
    cout << "Inside destructor " << std::hex << this << std::dec << endl;
  }

  void set(int i) { this->i = i; }
  int get() { return i; }
  int incr() { return i++; }

  void dump() {
    cout << std::hex << this << std::dec << " value of i " << i << endl;
  }

  Test operator =(Test &t)
  {
    cout << "= operator called " << std::hex << this << " from " << &t << std::dec << endl;
    return t;
  }
};

void check(const Test &t)
{
  cout << "pass by referecne " << endl;
}

Test checkRet(Test t)
{
  Test toRet;
  toRet = t;
  toRet.set(10);
  return toRet;
}

int main(int argc, char **argv)
{
  Test t;
  Test t1;
  t.set(10);
  t1 = checkRet(t);
  t.dump();
  t1.dump();
  return 0;
}

