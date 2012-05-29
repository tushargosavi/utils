#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <sequtils.h>

using namespace std;

class Person
{
private :
  std::string name;
public :
  Person(std::string n) : name(n) {
  }

  const std::string& getName() const {
    return name;
  }

  void print() const {
    std::cout << name << std::endl;
  }

  void printWithPrefix(std::string prefix) const {
    std::cout << prefix << name << std::endl;
  }
};

ostream& operator<<(ostream& os, const Person& p)
{
  os << "name : " << p.getName() << std::endl;
}

int main(int argc, char *argv[])
{
  const char *arr[] = {
    "Tushar",
    "Sagar",
    "Prefix1"
  };
  
  vector<Person> v1;
  for (int i = 0; i < 3; i++)
    v1.push_back(Person(arr[i]));
  
  print_seq(v1, "v1 :\n");
  for_each(v1.begin(), v1.end(),
	   mem_fun_ref(&Person::print));

  cout << "================================" << endl;
  for_each(v1.begin(), v1.end(),
	   bind2nd(mem_fun_ref(&Person::printWithPrefix),
		   "person: "));
  cout << endl;

  return 0;
}
