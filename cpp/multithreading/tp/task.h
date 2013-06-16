#ifndef TASK_H
#define TASK_H

namespace tsk { namsespace task {

  enum task_state {
    TASK_CREATED,
    TASK_WAITING,
    TASK_STARTED,
    TASK_COMPLETED
  };

  typedef error_code int;

  class base_task {
  protected :
    task_state state;
    error_code err;
  public :
    base_task():state(task_state::TASK_CREATED) {}

    void start() {
      state = task_state::TASK_STARTED;
      err = performTask();
      state = task_state::TASK_COMPLETED;
      taskCompleted();
    }

    virtual error_code performTask() = 0;
    virtual void taskCompleted() = 0;
  };

  class sync_task : public base_task {
  private :
    std::mutex _mutex;
    std::condition_variable _cond;

  public :
    void wait() {
      std::unique_lock<std::mutex> lck(_mutex);
      while (state != task_state::TASK_COMPLETED)
	wait(_lck);
    }
  }

  template<typename T>
    task_queue : cqueue<T*> {
  protrected :
    tsk::tpool::ThreadPool *p;
  private:
    task_queue() {
      p = new ThreadPool(10);
    }
    task_queue::pushTask(T *task) {
      add(task);
    }
    
    void wait() {
      p->wait();
    }
  }

} // namespace task
} // namespace tsk

