#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
  list<int> l;
  vector<int> v;
  int randValue;

  // create a vector with 10 random elements
  for (int i=0; i < 10; i++) {
    randValue = rand() % 100;
    v.push_back(randValue);
  }

  // print the list of vectors
  vector<int>::const_iterator pos;
  for (pos = v.begin(); pos != v.end(); ++pos) {
    cout << *pos << " ";
  }

  l.resize(v.size());
  std::copy(v.begin(), v.end(), l.begin());


  // print the list of vectors
  cout << endl;
  list<int>::const_iterator li;
  for (li = l.begin(); li != l.end(); ++li) {
    cout << *li << " ";
  }
  cout << endl;
  return 0;
}

