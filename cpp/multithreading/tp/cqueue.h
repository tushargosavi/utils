#ifndef CQUEUE_H
#define CQUEUE_H

#include <mutex>
#include <condition_variable>
#include <deque>

namespace tsk {
  class queue_empty_exception : public std::exception {
    std::string str;
  public :
    queue_empty_exception(std::string s):str(s) {}
  };
  
template<typename T>
class cqueue {
private:
  std::mutex _mutex;
  std::condition_variable _cond;
  std::deque<T> _queue;
  bool done;
  
public :
  cqueue<T>():done(false) {}
  
  void add(T msg) {
    bool notify = false;
    {
      std::lock_guard<std::mutex> lck(_mutex);
      if (_queue.empty()) notify=true;
      _queue.push_back(msg);
    }
    if (notify)
      _cond.notify_one();
  }
  
  T get() {
    std::unique_lock<std::mutex> lck(_mutex);
    while(!done && _queue.empty())
      _cond.wait(lck);
    
    // throw an exception so that callers of get will
    // come out of wait.
    if (done && _queue.empty())
      throw tsk::queue_empty_exception("No more work");
    
    T msg = _queue.back();
    _queue.pop_back();
    return msg;
  }
  
  void setDone() {
    done = true;
    _cond.notify_all();
  }
};

} // namespae tsk

#endif