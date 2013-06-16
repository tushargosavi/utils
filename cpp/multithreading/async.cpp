#include <iostream>
#include <thread>
#include <future>
#include <string>

std::string func() {
  std::string str("Hello from future!");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return str;
}


int main()
{
  auto ftr = async(&func);
  std::cout << "Hello from main!" << std::endl;
  std::string str = ftr.get();
  std::cout << str << std::endl;
  return 0;
}
