#include "tpool.h"

namespace tsk { namespace tpool
{
    void Thread::threadBody() {
      std::unique_lock<std::mutex> lck(_mutex);
      while(!_done) {
	
	while (!_busy && !_done)
	  _cond.wait(lck);
	
	// terminate is we are asked to stop
	if (_done)
	  break;
	
	lck.unlock();
	
	func();
	
	_pool->markFree(this);
	lck.lock();
	_busy = false;
	
      }
      _pool->setDestroyed(this);
    }
  }
}

