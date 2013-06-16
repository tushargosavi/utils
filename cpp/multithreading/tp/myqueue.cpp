#include <iostream>

template<typename T>
class Queue {
public :
  class QueueItem<T> {
    T *_elem;
    T *next;
  };

private:
  QueueItem<T> *_head;
  QuaueItem<T> *_tail;
  int _count;

public :
  Queue():_head(NULL), _tail(NULL), _count(0) { }
  T* head() { return _head; }
  T* tail() { return _tail; }
  int count() { return _count; }
  bool empty() { _head == NULL; }
  
  T* add(T* item);
  T* pop();
};

template<typename T>
T* Queue::add(T *elem)
{
  QueueItem<T> item(elem);
  if (head == NULL) {
    _head = _tail = item;
  } else {
    _tail->next = item;
    _tail = item;
  }
}

template<typename T>
T* Queue::pop()
{
  if (!_head) return NULL;
  T *elem = _head->item;
  delete item;
  return elem;
}
