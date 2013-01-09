#include <tbb/parallel_for.h>
#include <iostream>

using namespace std;
using namespace tbb;

int main(int argc, char *argv[])
{
  const static size_t N = 100000;
  parallel_for(size_t(0), N,
	       [] (int j) {
		 cout << "index " << j << endl;
	       });
  return 0;
}
