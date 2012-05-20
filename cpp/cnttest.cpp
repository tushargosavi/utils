#include <iostream>
#include <vector>
#include <set>
#include <sequtils.h>

using namespace std;

class Test {
private :
  int count;
public :
  /* default contructor */
  Test() : count(0) {}

  /*
  Test(Test &t) {
    cout << "copy constructor called " << endl;
    this->count = t.count;
  }
  */
  /* assignment operator */
  Test& operator=(Test t) {
    cout << "operator = called " << endl;
    if (this != &t) {
      this->count = t.count;
    }
    return *this;
  }

  ~Test() {
    cout << "calling destructor for object " << this << endl;
  }

  void inc() { count++; }
  void display() const { cout << "count of " << this << " is " << count << endl; }
  int getCount() const { return count; }
};

ostream& operator<<(ostream& os, const Test &t)
{
  os << "[ addr " << &t << " value  " << t.getCount() << "] " << endl;
  return os;
}

int main(int argc, char *argv[])
{
  Test t;
  vector<Test> v;
  for (int i=0; i < 10; i++) {
    t.inc();
    v.push_back(t);
  }
  print_seq(v, "v:\n ");

  vector<Test> v2 = v;
  print_seq(v2, "v2:\n ");

  vector<Test> v3(v.begin(), v.end());
  print_seq(v3, "v3\n ");
  cout << "printing old vector" << endl;
  print_seq(v, "v:\n ");

  vector<Test> v4(v);
  print_seq(v4, "v4\n ");
  cout << "printing old vector" << endl;
  print_seq(v, "v:\n ");

  v.clear();

  int intarr[] = { 1, 2, 6, 4, 93, 4 };
  set<int> intst(intarr, intarr + sizeof(intarr) / sizeof(intarr[0]));
  print_seq(intst, "st");

  cout << endl;  
  return 0;
}
