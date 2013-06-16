
#define __GXX_EXPERIMENTAL_CXX0X__
#define _GLIBCXX_USE_NANOSLEEP

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;

int main() {
  std::vector<std::thread> threads;
  for(int i =0; i < 10; ++i) {
    threads.push_back(std::thread([]() {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Hello world from thread \n";
    }));
  }
  cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
  for_each(threads.begin(), threads.end(),
      [](std::thread &th) {
        th.join();
          });

  return 0;
}


