#include <iostream>
#include <map>
#include <string>

using namespace std;

typedef multimap<int,string> IntStringMap;

int main(int argc, char *argv[])
{
  IntStringMap m;
  map<string, float> aa;

  m.insert(make_pair(1, string("Tushar")));
  m.insert(make_pair(2, string("Ravindranath")));
  m.insert(make_pair(3, string("Gosavi")));

  IntStringMap::const_iterator pos;
  for (pos = m.begin(); pos != m.end(); ++pos) {
    cout << "key " << pos->first << " value " << pos->second << endl;
  }
  cout << endl;

  cout << "Testing of associative array " << endl;
  aa["PI"] = 3.14159;
  aa["VAT"] = 12.34;
  aa["some arbit value"] = 12394.33746;

  map<string, float>::const_iterator aai;
  for (aai = aa.begin(); aai != aa.end(); ++ aai) {
    cout << "key " << aai->first << " value " << aai->second << endl;
  }

  cout  << endl;
  return 0;
}
