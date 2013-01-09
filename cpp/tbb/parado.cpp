#include <iostream>
#include <tbb/parallel_do.h>
#include <list>

using namespace std;
using namespace tbb;

static const size_t N = 10000000;

int main(int argc, char *argv[])
{
  list<float> fl;
  for(size_t i = 0; i < N ; ++i) {
    fl.push_back(random());
  }

  parallel_do(fl.begin(), fl.end(),
	      [=] (float v) {
		cout << "value of float " << v << endl;
	      });
  return 0;
}
