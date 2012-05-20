#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef multimap<string,string> StrStrMap;
typedef map<float, float> FloatFloatMap;

template<typename K, typename V>
class value_equals {
private :
  V value;
public  :
  value_equals(const V& v) : value(v) { }
  bool operator() (pair<const K,V> elem) {
    return elem.second == value;
  }
};

void test_find(void);

int main(int argc, char *argv[])
{
  StrStrMap dict;
  dict.insert(make_pair("day", "Tag"));
  dict.insert(make_pair("strage", "frem"));
  dict.insert(make_pair("Cat",  "Auto"));
  dict.insert(make_pair("smart", "elegant"));
  dict.insert(make_pair("trait", "Merkmal"));
  dict.insert(make_pair("smart", "something"));

  StrStrMap::iterator pos;
  cout.setf(ios::left, ios::adjustfield);
  cout << ' ' << setw(10) << "english" << "german" << endl;
  cout << setfill('-') << setw(20) << ""
       << setfill('-') << endl;
  for(pos = dict.begin(); pos != dict.end(); ++pos)
    cout << ' ' << setw(10) << pos->first.c_str()
	 << pos->second << endl;
  cout << endl;

  string word("smart");
  cout << word << endl;
  for(pos = dict.lower_bound(word); pos != dict.upper_bound(word); ++pos)
    cout << " " << pos->second << endl;

  cout << "=================Testing Find ===============" << endl;
  test_find();
  return 0;
}


void test_find() {
  FloatFloatMap col;
  FloatFloatMap::iterator pos;

  col[1] = 7;
  col[2] = 4;
  col[3] = 2;
  col[4] = 3;
  col[5] = 6;
  col[6] = 1;
  col[7] = 3;

  pos = col.find(3.0);
  if (pos != col.end()) 
    cout << pos->first << " " << pos->second << endl;

  pos = find_if(col.begin(), col.end(),
		value_equals<float,float>(3.0));
  if (pos != col.end())
    cout << pos->first << " " << pos->second << endl;
}
