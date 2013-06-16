/*
  g++ -g2 -std=c++11 -o test -D__GXX_EXPERIMENTAL_CXX0X__ -D_GLIBCXX_USE_NANOSLEEP test.cpp  -pthread
*/
#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <algorithm>

std::string func() {
  std::string str("Hello from future!");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return str;
}

int main()
{
  std::vector<std::future<void>> futures;
  std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
  for(int i = 0; i < 10; ++i) {
    auto ftr = std::async(std::launch::async, []() {
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << std::this_thread::get_id() << std::endl;
      });
    futures.push_back(std::move(ftr));
  }
  std::cout << "waiting for all async task to finish" << std::endl;
  std::for_each(futures.begin(), futures.end(),
		[](std::future<void> &ftr) {
		  ftr.wait();
		});
  std::cout << "Waiting for main to stop" << std::endl;
  return 0;
}
