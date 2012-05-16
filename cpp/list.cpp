#include <list>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  list<char> lst;
  
  for (char c='a'; c <= 'z'; c++)
    lst.push_back(c);

  list<char>::const_iterator pos;
  for (pos = lst.begin(); pos != lst.end(); pos++)
    cout << *pos<< endl;

  cout << endl;

  return 0;
}

