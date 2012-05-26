#ifndef CARRAY_H
#define CARRAY_H

#include <cstddef>

template<typename T, size_t thesize>
class carray {
private :
  T v[thesize];
public :
  typedef T value_type;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  iterator begin() { return v; }
  const_iterator begin() const { return v; }

  iterator end() { return v+thesize; }
  const_iterator end() const { return v+thesize; }

  reference operator[](size_t i) { return v[i]; }
  const_reference operator[](size_t i) const { return v[i]; }

  size_type size() const { return thesize; }
  size_type max_size() const { return thesize; }

  T* as_array() { return v; }
};

#endif
