#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

bool lessThan(string s1, string s2)
{
  return s1.length() < s2.length();
}

int main(int argc, char *argv[])
{
  string sarr[] = {
    "1xx", "2x", "3x", "4x", "5xx", "6xxxxx", "7xx", "8xxx", "9xx",
    "10xxx", "11", "12", "13", "14xxx", "15", "16", "17" };
  vector<string> s1;
  vector<string> s2;

  int numElem = sizeof(sarr) / sizeof(sarr[0]);
  copy(sarr, sarr + numElem,
       back_inserter(s1));
  print_seq(s1, "s1 : ");
  s2 = s1;

  sort(s1.begin(), s1.end(), lessThan);
  print_seq(s1, "sort: ");
  
  print_seq(s2, "s2  : ");
  stable_sort(s2.begin(), s2.end(), lessThan);
  print_seq(s2, "s2  : ");
  return 0;
}
