#include <iostream>
#include <future>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

template<typename T>
class cqueue {
private:
  std::mutex _mutex;
  std::condition_variable _cond;
  std::deque<T> _queue;
  bool done;

public:
  cqueue():done(false) { }

  void add(T msg) {
    {
      std::lock_guard<std::mutex> lck(_mutex);
      _queue.push_back(msg);
    }
    _cond.notify_one();
  }

  T get() {
    std::unique_lock<std::mutex> lck(_mutex);
    while (!done && _queue.empty())
      _cond.wait(lck);
    if (done)
      throw std::exception();
    T msg = _queue.back();
    _queue.pop_back();
    return msg;
  }

  void setDone() {
    done = true;
    _cond.notify_all();
  }
};

void dirTraversalThrd(cqueue<path> &dirList,
		      cqueue<path> &fileList)
{
  try {
    for(;;) {
      path dir = dirList.get();
      if (!exists(dir))
	return;
      for(directory_iterator it(dir);
	  it != directory_iterator();
	  ++it) {
	if (is_directory(it->status()))
	  dirList.add(it->path());
	else
	  fileList.add(it->path());
      }
    }
  }catch(...) {
    std::cout << "Exiting from traversal thread " << std::endl;
  }
}

void printThread(cqueue<path> &fileList)
{
  try {
    for(;;) {
      path p = fileList.get();
      std::cout << p << std::endl;
    }
  }catch(...) {
    std::cout << "print thread exiting .... ";
  }
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage " << argv[0] << " <directory> " << std::endl;
    return -1;
  }
  cqueue<path> dirList;
  cqueue<path> fileList;
  dirList.add(path(argv[1]));
  std::vector<std::future<void>> futures;

  // start 16 thread to get directory listing in parallel.
  for(int i = 0; i < 16; ++i) {
    future<void> ftr = std::async(std::launch::async, dirTraversalThrd,
				    std::ref(dirList),
				    std::ref(fileList));
    futures.push_back(std::move(ftr));
  }
  auto ftr = std::async(std::launch::async, printThread,
			std::ref(fileList));
  futures.push_back(std::move(ftr));

  // stop everything after 60 seconds.
  sleep(60);
  dirList.setDone();
  fileList.setDone();
  
  // wait for all 16 thread to finish.
  while(!futures.empty()) {
    auto ftr = std::move(futures.back());
    futures.pop_back();
    ftr.wait();
  }
  return 0;
}

