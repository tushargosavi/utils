#include <iostream> 
#include <mutex>
#include <future>
#include <condition_variable>
#include <deque>
#include <ctime> 
#include <boost/filesystem.hpp> 

template<typename T>
class CuncurrentQueue {
protected:
  std::mutex _mutex;
  std::condition_variable _cond;
  std::deque<T> _queue;
  bool done;

public :

  CuncurrentQueue<T>():done(false) { };

  void add(T msg) {
    {
      std::lock_guard<std::mutex> lck(_mutex);
      _queue(std::move(msg));
    }
    _cond.notify_one();
  }

  T get() {
    std::unique_lock<std::mutex> lck(_mutex);
    while (!done && _queue.empty())
      _cond.wait(lck);
    // If no item to be process then throw an exception, so that
    // caller client will handle it and come out of the loop.
    if (done)
      throw std::exception();
    
    T msg = _queue.back();
    _queue.pop_back();
    return msg;  
  }
  
  void markDone() {
    done = true;
    _cond.notify_all();
  }
};

void listDirectory(CuncurrentQueue<boost::filesystem::path> &dirQueue,
		   CuncurrentQueue<boost::filesystem::path> &fileQueue)
{
  try {
    for(;;) {
      auto p = dirQueue.get();
      for(boost::filesystem::directory_iterator it(p);
	  it != boost::filesystem::directory_iterator();
	  ++it) {
	if (boost::filesystem::is_directory(it->status()))
	  dirQueue.add(std::move(it->path()));
	else
	  fileQueue.add(it->path());
      }
    }
  } catch(...) {
    std::cout << "Terminating listDirectory thread" << std::endl;
  }
}

void printListing(CuncurrentQueue<boost::filesystem::path> &fileQueue)
{
  try {
    for(;;) {
      auto p = fileQueue.get();
      std::cout << p << std::endl;
    }
  }catch(...) {
    std::cout << "Terminating print thread" << std::endl;
  }
}

int main(int argc, char **argv) 
{
  boost::filesystem::path p(argv[1]);
  CuncurrentQueue<boost::filesystem::path> dirQueue;
  CuncurrentQueue<boost::filesystem::path> fileQueue;
  std::vector<std::future<void>> futures;

  dirQueue.add(p);
  for(int i = 0; i < 16; ++i) {
    auto ftr = std::async(std::launch::async, &listDirectory,
			  std::ref(dirQueue),
			  std::ref(fileQueue));
    futures.push_back(std::move(ftr));
  }
  auto ftr = std::async(std::launch::async, &printListing,
	     std::ref(fileQueue));
  futures.push_back(std::move(ftr));

  while (!futures.empty()) {
    auto ftr = std::move(futures.back());
    futures.pop_back();
    ftr.wait();
  }
  return 0;
}
