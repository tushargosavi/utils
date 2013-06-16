#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

void handler1(const boost::system::error_code &ec)
{
  std::cout << "5 s. " << std::endl;
}

void handler2(const boost::system::error_code &ec)
{
  std::cout << " 10 s " << std::endl;
}

boost::asio::io_service io_service;

void run()
{
  io_service.run();
}

int main(int argc, char **argv)
{
  boost::asio::deadline_timer t1(io_service, boost::posix_time::seconds(5));
  t1.async_wait(handler1);
  boost::asio::deadline_timer t2(io_service, boost::posix_time::seconds(10));
  t2.async_wait(handler2);
  boost::thread th1(run);
  boost::thread th2(run);
  th1.join();
  th2.join();
}
