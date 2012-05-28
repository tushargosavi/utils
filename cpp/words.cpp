#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sequtils.h>

using namespace std;

int main(int argc, char *argv[])
{
  vector<string> words;
  string inStr =" this    is a demo  string  nw";
  string word;

  string::iterator pos;
  for (pos = inStr.begin(); pos != inStr.end(); ++pos) {
    if (*pos == ' ') {
      if (word.size() > 0) {
	words.push_back(word);
	word.clear();
      }
    } else {
      word.push_back(*pos);
    }
  }

  if (word.size() > 0)
    words.push_back(word);

  print_seq(words);

  return 0;
}
