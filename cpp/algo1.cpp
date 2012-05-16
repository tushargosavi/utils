#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
  vector<int> i1;
  vector<int> i2;
  int randValue;

  // create a vector with 10 random elements
  for (int i=0; i < 10; i++) {
    randValue = rand() % 100;
    i1.push_back(randValue);
  }

  // print the list of vectors
  vector<int>::const_iterator pos;
  for (pos = i1.begin(); pos != i1.end(); ++pos) {
    cout << *pos << " ";
  }
  cout << std::endl;

  vector<int>::const_iterator minValue = min_element(i1.begin(), i1.end());
  cout << "Min value is " << *minValue << endl;

  vector<int>::const_iterator maxValue = max_element(i1.begin(), i1.end());
  cout << "Max element is " << *maxValue << endl;

  // Sort all elements
  sort(i1.begin(), i1.end());
  for (pos = i1.begin(); pos != i1.end(); ++pos) {
    cout << *pos << " ";
  }
  cout << endl;
  cout << "Reversing half of the element after " << i1[5] << endl;
  vector<int>::iterator match = find(i1.begin(), i1.end(), i1[5]);
  // reverse half of the element
  reverse(match, i1.end());
  for (pos = i1.begin(); pos != i1.end(); ++pos) {
    cout << *pos << " ";
  }
  cout << std::endl;

  cout << "searching for element 105 which is not present in the list " << endl;
  pos = find(i1.begin(), i1.end(), 105);
  if (pos == i1.end()) {
    cout << "Element not found in the list " << endl;
  } else {
    cout << "Element found in the list " << endl;
  }
  return 0;
}
