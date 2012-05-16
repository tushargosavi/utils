#include <iostream>
#include <memory>
#include <assert.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Dumpable {
public :
  virtual void dump(void) = 0;
}; 

class ReferenceCountedObject : public Dumpable {
protected:
  int refCount;

public :
  ReferenceCountedObject():refCount(1) {
    std::cout << "ReferenceCountedObject Constructor called Ptr=0x"
	      << std::hex << this << endl;
  }

  virtual ~ReferenceCountedObject() {
    std::cout << "ReferenceCountedObject destructore called " << refCount
	      << " Ptr 0x" << std::hex << this <<  endl;
  }

  inline void get() {
    refCount++;
  }

  inline void put() {
    refCount --;
    assert(refCount >= 0); // referece count should not go to zero
  }

  inline int getCount() { return refCount; }
  inline void set(int count) { this->refCount = count; }
  inline void dump(void) { cout << "Value of count is " << refCount << endl; }
};

class AutoDestroyableObject : public ReferenceCountedObject
{
public :
  virtual void put()
  {
    ReferenceCountedObject::put();
    if (refCount == 0)
      delete this;
  }
};

/* at exit function does not gets called at signal handler */
void exit_handler(void)
{
  cout << "About to exit the program " << endl;
}

int main(int argc, char **argv)
{
  atexit(&exit_handler);
  return 0;
}
