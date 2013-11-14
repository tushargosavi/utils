#include <iostream>
#include <string.h>

bool is_palin(const char *str, int start, int end) {
  bool ret = true;
  while (start < end)
    if (str[start++] != str[end--])
      return false;
  
  return true;
}


// navie approach to solution, require n ** 3 algo.
int count_palins(const char *str) {
  int total = 0;
  int len = strlen(str);
  for(int i = 0; i < len; i++) 
    for(int j = i; j < len; j++)
      if (is_palin(str, i, j))
	total++;
     
  return total;
}

// count number of palindroms in a string.
// The string (i,j) is a palindrom if string (i+1, j-1) is a palindrom and str[i] == str[j]
// use a table to store known palindroms.
// this takes n ** 2 complexity.
int count_palins1(const char *str) {
  int len = strlen(str);
  int arr[len][len];
  int total = 0;

  // zero out the array.
  memset(arr, len * len, 0);

  for(int k = 0; k < len; k++) {
    for(int i = 0; i < len - k; i++) {
      int j = i + k;
      if ( (i == j)  ||  // a single char is a palindrom
	   ((i+1 == j) && str[i] == str[j]) || // a two char string is palindrom is first and next char are equal
	   ((arr[i+1][j-1] == 1) && str[i] == str[j])) { // else (i+1, j-1) is palindrom and start and end char are equal.
	arr[i][j] = 1;
	total++;
      }
    }
  }

  return total;
}


int main(int argc, char **argv)
{
  const char *str = argv[1];
  int len = strlen(str);
  std::cout << "Is Palin " << is_palin(str, 0, len - 1) << std::endl;
  std::cout << "Total palindroms " << count_palins(str) << std::endl;
  std::cout << "Total palindroms " << count_palins1(str) << std::endl;
  return 0;
}
