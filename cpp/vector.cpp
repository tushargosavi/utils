#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  vector<int> arr;
  
  for (int i=0; i < 6; i++)
    arr.push_back(i);

  for(int i=0; i < arr.size(); i++)
    cout << "Element at index " << i << " is " << arr[i] << endl;
  
  return 0;
}

