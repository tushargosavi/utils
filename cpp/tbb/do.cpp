#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

static const size_t N = 10000000;

int main(int argc, char *argv[])
{
  list<float> fl;
  for(size_t i = 0; i < N ; ++i) {
    fl.push_back(random());
  }

  for_each(fl.begin(), fl.end(),
	   [=] (float v) {
	     cout << "value of float " << v << endl;
	   });
  return 0;
}
