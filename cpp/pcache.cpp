#include <iostream>
#include <deque>

using namespace std;

class pCacheHandler : public ListItem {
};

class pCacheHome : public ListItem {
};

class BaseTask {
public:
  virtual void init() = 0;
  virtual void start()= 0 ;
  virtual void done()= 0;

  virtual void childDone(BaseOperation *child) =  0;

private :
  deque<BaseOperation*> children;
  void addChild(BaseOperation *child) {
    children.push_back(child);
  }
};


class TaskList {
private :
  deque<BaseTask*> list;
public :
  void addNewTask(BaseTask *task) {
    list.push_back(task);
  }

  BaseTask *getNextToRun() {
    return list.head();
  }

};

class pCacheOperation : public BaseTask {
public :
  virtual void init() { }
  virtual void start() { }
  virtual void done() { }
};

int main(int argc, char *argv[])
{
  pCacheOperation *op = new pCacheOperation();
  pCacheOperation *ch1 = new pCacheOperation();

  op.addChild(ch1);
  sleep(10);
  ch1.done();
  cout << "Hello world" << endl;
  return 0;
}
