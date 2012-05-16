#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> col1;
  for (int i = 0 ; i < 20 ; ++i) {
    col1.push_back(i);
  }

  copy(col1.rbegin(), col1.rend(),
       ostream_iterator<int>(cout, " "));
  cout << endl;

  return 0;
}
