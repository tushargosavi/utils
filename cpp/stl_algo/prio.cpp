#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
  priority_queue<int> queue;
  int arr[] = { 1, 3, 5, 6, 7, 3, 6, 1 };
  for(int i =0 ; i < sizeof(arr) / sizeof(arr[0]); ++i) {
    queue.push(i);
  }
  
  cout << queue.top() << endl;
  queue.pop();
  cout << queue.top() << endl;
  queue.pop();
  
  return 0;
}
