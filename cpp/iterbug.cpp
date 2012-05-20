#include <iostream>
#include <vector>
#include <algorith>

using namespace std;

int main(int argc, char *argv[])
{
  vector<int> v1;
  vector<int> v2;

  vector<int>::iterator pos = v1.begin();
  reverse(++pos, v1.end());

  return 0;
}
