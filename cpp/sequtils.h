#ifndef SEQUTILS_H
#define SEQUTILS_H

#include <string>
#include <algorithm>
#include <iterator>

template<typename T>
void print_sequence(const T &t)
{
  typename T::const_iterator pos;
  for (pos = t.begin(); pos != t.end(); ++pos) {
    std::cout << *pos << " ";
  }
  std::cout << std::endl;
}

template<typename T>
void print_seq(const T &t, const std::string name = "")
{
  typename T::const_iterator pos;

  std::cout << name << " : ";
  std::copy(t.begin(), t.end(),
	    std::ostream_iterator<typename T::value_type>(std::cout, " "));
  std::cout << std::endl;
}

/* returns a give sequence of n random integers */
template<typename T>
void populate_lseq(T &t, int count)
{
  for (int i = 0 ; i < count ; ++i) {
    t.insert(t.end(), i);
  }
}

#endif
