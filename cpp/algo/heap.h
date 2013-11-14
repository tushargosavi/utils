#ifndef __HEAP_H
#define __HEAP_H

#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>

template <typename T, typename Cmp = std::less<T> >
class Heap {
private:
  std::vector<T> heap_arr;
  int len;

  inline int pidx(int n) { return (n-1) / 2; }
  inline int c1idx(int n ) { return n * 2 + 1; }
  inline int c2idx(int n ) { return n * 2 + 2; }

public:
  Heap(): len(0) {}
  Heap(std::vector<T> arr) {
    heap_arr.resize(arr.size());
    std::copy(arr.begin(), arr.end(), heap_arr.begin());
    len = arr.size();
    make_heap();
  }

  bool verify() {
    Cmp __cmp__ = Cmp();
    for(int i = 0; i < len; i++) {
      int c1 = c1idx(i);
      int c2 = c2idx(i);
      if (c1 < len && !__cmp__(heap_arr[i],heap_arr[c1]))
	return false;
      if (c2 < len && !__cmp__(heap_arr[i],heap_arr[c2]))
	return false;
    }
    return true;
  }

  int size() { return len; }
  bool empty() { return (len == 0); }

  void make_heap() {
    for(int i = len/2; i >= 0; i--) {
      push_down(i);
    }
  }

  void push_up(int n) {
    Cmp __cmp__ = Cmp();
    int p = pidx(n);
    while (n > 0 && !__cmp__(heap_arr[p], heap_arr[n])) {
      std::swap(heap_arr[p], heap_arr[n]);
      n = p;
      p = pidx(n);
    }
  }

  void push_down(int n) {
    Cmp __cmp__ = Cmp();

    // iterate until the item at leaf or heap property is
    // maintaied.

    // if childidex is greater than heap size then the item is
    // a leaf.    
    while (c1idx(n) <= len-1) {

      // calculate index of minimum child.
      int c1 = c1idx(n);
      int min_idx = ((c1 < len-1) && !__cmp__(heap_arr[c1],heap_arr[c1+1]))? (c1+1) : c1;

      // If root is less than both of its children, then
      // heap property is satisfied, , no need to go further down.
      if (__cmp__(heap_arr[n], heap_arr[min_idx]))
	break;

      std::swap(heap_arr[n], heap_arr[min_idx]);
      n = min_idx;
    }
  }

  void add(T elem) {
    heap_arr.push_back(elem);
    len++;
    push_up(len);
  }

  T remove() {
    T elem = heap_arr[0];
    std::swap(heap_arr[0], heap_arr[len-1]);
    len--;
    push_down(0);
    heap_arr.pop_back();
    return elem;
  }

  void debug() {
    std::cout << " size " << len << " " ;
    std::copy(heap_arr.begin(), heap_arr.end(),
	      std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
};

#endif
