#ifndef SEQUTILS_H
#define SEQUTILS_H

#include <string>
#include <algorithm>
#include <iterator>
#include <time.h>

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
  
  std::cout << name;
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

/* check if given sequence is sorted or not */
template<typename T>
bool is_sorted_seq(T &t, bool asc = true) {
  typedef typename T::value_type TValue;
  if (asc)
    return is_sorted(t.begin(), t.end());
  else
    return is_sorted(t.begin(), t.end(), [](TValue &a, TValue &b) {
	if (a>b) return true; else return false;
      });
}


/* returns a give sequence of n random integers */
template<typename T>
void populate_lseq(T &t, int start, int end)
{
  for (int i = start ; i < end ; ++i) {
    t.insert(t.end(), i);
  }
}

template<typename T>
void populate_rand(T &t, int count, int max = 1000)
{
  typename T::value_type v;
  for (int i = 0; i < count ; ++i) {
    v = rand() % max;
    t.insert(t.end(), v);
  }
}

// initialize random number generator with seed as
// current time when program is started , without
// calling it explicitely.
void random_init() __attribute__((constructor));

void random_init()
{
  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);
}

#endif
