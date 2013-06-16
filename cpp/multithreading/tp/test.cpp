#define _GLIBCXX_USE_NANOSLEEP

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>

bool done = false;

template<typename T>
class CuncurrentQueue {
private:
  std::queue<T*> queue;
  std::mutex m;
  std::condition_variable cond;
public:
  /* Does nothing */
  CuncurrentQueue() {}

  /* Add a new item to the queue, also send a signal
     if queue was empty, so that waiters waiting for
     new item will continue */
  void push(T*);

  /* Remote a item from the queue, if there is no
     item in the queue, then wait till a item is
     added */
  T* pop();
};

template<typename T>
CuncurrentQueue::push(T* item)
{
  m.lock();
  bool notify = queue.emtpy();
  queue.push(item);
  if (notify)
    cond.notify_one();
  m.unlock();
}

template<typename T>
T* CuncurrentQueue::pop() {
  m.lock();
  if (queue.empty())
    cond.wait(m);
  T* tmp = queue.front();
  queue.pop()
  m.unlock();
  return tmp;
}

void producer() {
  for(int i = 0; i < 10; ++i) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Producer Producing item " << i << std::endl;
    queue.push(&i);
  }
  done = true;
}

void consumer() {
  int *i;
  while (!done) {
    i = queue.pop();
    std::cout << "processing item " << *i << std::endl;
  }
}
    

int main(int argc, char **argv)
{
  std::thread pro(producer);
  std::thread con(consumer);
  pro.join();
  con.join();
  return 0;
}
