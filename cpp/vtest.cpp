#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
  vector<string> sentence;
  sentence.reserve(5);

  sentence.push_back("Hello");
  sentence.push_back("How");
  sentence.push_back("Are");
  sentence.push_back("You");
  sentence.push_back("?");

  copy(sentence.begin(), sentence.end(),
       ostream_iterator<string>(cout, " "));
  cout << endl;

  cout << "max size " << sentence.max_size() << endl;
  cout << "size : " << sentence.size() << endl;
  cout << "capacity " << sentence.capacity() << endl;

  swap(sentence[1], sentence[3]);
  sentence.insert(find(sentence.begin(), sentence.end(), "?"), "always");
  sentence.back() = "!";


  copy(sentence.begin(), sentence.end(),
       ostream_iterator<string>(cout, " "));
  cout << endl;

  cout << "max size " << sentence.max_size() << endl;
  cout << "size : " << sentence.size() << endl;
  cout << "capacity " << sentence.capacity() << endl;

  return 0;
}
