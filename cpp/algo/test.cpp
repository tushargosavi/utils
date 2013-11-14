#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv) {
  int n = atoi(argv[1]);
  
  for(int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      for(int k = i; k < j; k++) { 
	cout << "( " <<  i << ", " << j << " ," << k << ")" << "( " << i << ", " << k << ") (" << k+1 << ", " << j << ")" << endl;
      }

  cout << "==========================" << endl;

  for(int s =0; s < n; s++) 
    for (int i = 0; i < n - s; i++) {
      int j = i + s;
      for(int k = i; k < j; k++) 
	cout << "( " <<  i << ", " << j << " ," << k << ")" << "( " << i << ", " << k << ") (" << k+1 << ", " << j << ")" << endl;

    }
      
  return 0;
}
