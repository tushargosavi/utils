#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
  deque<string> col;
  col.assign(3, string("string"));
  col.push_back("last string");
  col.push_front("first string");
  
  copy(col.begin(), col.end(),
       ostream_iterator<string>(cout, "\n"));
  cout << endl;

  col.pop_front();
  col.pop_back();
  
  for (int i = 1; i < col.size(); ++i)
    col[i] = "another " + col[i];

  col.resize(4, "resized string");


  copy(col.begin(), col.end(),
       ostream_iterator<string>(cout, "\n"));
  cout << endl;
  
  return 0;
}
