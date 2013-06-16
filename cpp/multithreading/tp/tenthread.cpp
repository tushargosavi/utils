#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
  std::vector<std::thread> workers;
  for(int i = 0; i < 10; ++i) {
    workers.push_back(std::thread([i]() {
	  std::cout << "Hi from thread! " << i << "\n";
	}));
  }

  std::cout << "Hi, I am from main\n";
  std::for_each(workers.begin(), workers.end(),
		[](std::thread &th)
		{
		  th.join();
		});
  return 0;
 }
