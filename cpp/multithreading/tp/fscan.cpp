#include "tpool.h"
#include "task.h"

public FileSystemScanTask : public tsk::task::sync_task {
 private :
  path dir;
 public :
  void performTask() {
    if (!exists(dir))
      return;
    for(directory_iterator it(dir);
	it != directory_iterator();
	++it) {
      if (is_directory(it->status()))
	q.pushTask(it->path());
      else
	handleFile(it->path());
    }
  }

  void handleFile(path file) {
    std::cout << file << std::endl;
  }

  void taskCompleted() { }
};

void main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage " << argv[0] << " <directory> " << std::endl;
    return -1;
  }
  FileSystemScanTask tsk(path(argv[1]));
  tsk::task::task_queue<FileSystemScanTask> q;
  q.pushTask(&tsk);
  q.waitForAll();
}
