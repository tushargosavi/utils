#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

void print_list(const list<int> &l1,  const list<int> &l2)
{
  cout << "list 1 : " ;
  copy(l1.begin(), l1.end(), ostream_iterator<int>(cout, " "));
  cout << endl << "list 2 : ";
  copy(l2.begin(), l2.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
}

int main(int argc, char *argv[])
{
  list<int> list1,list2;
  for (int i = 0; i < 6; ++ i) {
    list1.push_back(i);
    list2.push_front(i);
  }
  print_list(list1, list2);

  list2.splice(find(list2.begin(), list2.end(), 3), list1);
  print_list(list1, list2);

  /* move first element to the end */
  list2.splice(list2.end(),
	       list2,
	       list2.begin());
  print_list(list1, list2);

  list2.sort();
  list1 = list2;
  list2.unique();
  print_list(list1, list2);
  
  list1.merge(list2);
  print_list(list1, list2);

  return 0;
}
