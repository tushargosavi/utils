#ifndef TPOOL_H
#define TPOOK_H

#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iterator>
#include <functional>
#include <condition_variable>

#include <iostream>

namespace tsk { namespace tpool 
{

class no_thread_exception : public std::exception {
};

class ThreadPool;

class Thread {
public :
  std::thread *_thrd;
  bool _busy;
  bool _done;
  std::mutex _mutex;
  std::condition_variable _cond;
  std::function<void(void)> func;
  ThreadPool *_pool;
  
public:
  
  Thread(ThreadPool *parent) {
    _busy = false;
    _done = false;
    _pool = parent;
    _thrd = new std::thread(&Thread::threadBody, this);
  }
  
  // wait for underline thread to finish.
  void join() { 
    std::cout << "Waiting for thread to join " << std::endl;
    _thrd->join(); 
    
  }
  
  void markDone() {
    std::lock_guard<std::mutex> lck(_mutex);
    _done = true;
    _cond.notify_all();
  }
  
  void setFunction(std::function<void(void)> func) {
    this->func = func;
    _cond.notify_all();
  }
  
  void threadBody();
};

class ThreadPool {
private:
  std::deque<Thread*> threads;
  std::deque<Thread*> free_threads;
  
  int desiredSize;
  std::mutex _tp_mutex;
  std::condition_variable _tp_cond;
  
public:
  ThreadPool(int size) {
    _tp_mutex.lock();
    desiredSize = size;
    // pre initialize list of threads
    for(int i =0; i < size; ++i) {
      Thread *trd = new Thread(this);
      free_threads.push_back(trd);
      threads.push_back(trd);
    }
    _tp_mutex.unlock();
  }
  
  int size() { return threads.size(); }
  int setSize(int s) {
    desiredSize = s;
  }
  void markFree(Thread *thrd) {
    if (desiredSize < size())
      thrd->markDone();
    else
      free_threads.push_front(thrd);
  }
  
  Thread *getThread() {
    std::lock_guard<std::mutex> lck(_tp_mutex);
    
    // First try to get thread from from free list of threads.
    if (!free_threads.empty()) {
      Thread *thrd = free_threads.front();
      free_threads.pop_front();
      return thrd;
    }
    if (desiredSize > size())
      return NULL;
    Thread *thr = new Thread(this);
    threads.push_back(thr);
    return thr;
  }
  
  void startThread(std::function<void(void)> func)
  {
    Thread *thr = getThread();
    thr->_busy = true;
    if (thr == nullptr)
      throw no_thread_exception();
    thr->setFunction(func);
  }
  
  void cleanupAndWait() {
    
    std::cout << "Cleanup and wait called " << std::endl;
    desiredSize = 0;
    std::for_each(threads.begin(), threads.end(),
		  [](Thread *th) {
		    th->markDone();
		  });
    wait();
  }
  
  void wait() {
    std::unique_lock<std::mutex> lck(_tp_mutex);
    desiredSize = 0;
    std::for_each(threads.begin(), threads.end(),
		  [](Thread *th) {
		    th->join();
		  });
  }
  
  void setDestroyed(Thread *th) {
    // TODO remove from threads and free_threads
  }
};
}}

#endif
