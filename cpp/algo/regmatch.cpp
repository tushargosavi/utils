#include <stdio.h>
#include <iostream>

bool match(const char *patt, const char *str) {

  // If pattern and string has finished then match is found
  if (*patt == 0 && *str == 0) return true;

  // If string has finished but there are still pending characters
  // in pattern, then no matched.
  if (*str == 0 && *patt) return false;

  // If pattern has finished but string is not finished,
  // then no matched.
  if (*patt == 0 && *str) return false;

  switch(*patt) {
  case '*' :
    // In case of *, check for three cases
    // * does not matches with any thing, 1.
    // * matches with one or more characters.
    // * matches with one character *
    return (match(patt+1, str) || 
	    match(patt, str+1) ||
	    match(patt+1, str+1));
  case '?' :
    // ? matches with exactly one characters.
    return (match(++patt, ++str));
  default :
    // If char matches then match next strings.
    if (*patt == *str)
      return match(++patt, ++str);
    else
      return false;
  }
  return false;
}

int main(int argc, char **argv)
{
  const char *pattern;
  const char *str;
  int idx;

  if (argc < 2) {
    std::cerr << "Usage %s <pattern> <str>\n";
    return -1;
  }

  pattern = argv[1];
  str = argv[2];
  
  if (match(pattern, str)) {
    std::cout << "Match found " << std::endl;
  } else {
    std::cout << "Match not found " << std::endl;
  }

  return 0;
}
  
