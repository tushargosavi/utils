#include <iostream>
#include <thread>
#include <future>
#include <string>

void thFunc(std::promise<std::string> && prm)
{
  std::string str("Hello from future!");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  prm.set_value(str);
}

int main()
{
  std::promise<std::string> prm;
  std::future<std::string> ftr = prm.get_future();
  std::thread th(&thFunc, std::move(prm));
  std::cout << "Hello from main!" << std::endl;
  std::string str = ftr.get();
  std::cout << str << std::endl;
  th.join();
  return 0;
}
