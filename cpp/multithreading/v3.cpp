#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

struct List {
  struct _Node {
    int _x;
    struct _Node *next;
    
    _Node(int x) : _x(x), next(nullptr) {}
  };



  _Node *_head;
  List(): _head(nullptr) {}

  void insert(int x) {
    auto node = new _Node(x);
    node->next = _head;
    _head = node;
  }

  /* count number of elements in the list */
  int count() {
    auto tmp = _head;
    int num = 0;
    while(tmp != nullptr) {
      tmp = tmp->next;
      num++;
    }
    return num;      
  }
};

  
void thFunc(List & lst)
{
  // insert 100 items in the list
  for(int i =0; i < 100; i++)
    lst.insert(i);
}

int main()
{
  List lst;
  std::vector<std::thread> workers;
  for(int i =0; i < 10; ++i)
    workers.push_back(std::thread(thFunc, std::ref(lst)));
  std::for_each(workers.begin(), workers.end(),
		[](std::thread &th) {
		  th.join();
		});
  std::cout << "The number of elements in the lists are " << lst.count()
	    << std::endl;
  return 0;
}
