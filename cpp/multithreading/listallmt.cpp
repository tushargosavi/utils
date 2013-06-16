#include <iostream>
#include <future>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

struct result {
  vector<path> dirs;
  vector<path> files;
};

result listDirectory(path dir)
{
  result res;
  if (!exists(dir))
    return;
  for(directory_iterator it(dir);
      it != directory_iterator();
      ++it) {
    if (is_directory(it->status()))
      res.dirs.push_back(it->path());
    else
      res.files.push_back(it->path());
  }
  return res;
}

int main(int argc, char **argv)
{
  vector<path> dirs;
  vector<path> files;
  if (argc < 2) {
    std::cerr << "Usage " << argv[0] << " <directory> " << std::endl;
    return -1;
  }
  dirs.push_back(path(argv[1]));
  while(!dirs.empty()) {
    std::vector<std::future<result>> futures;

    // start 16 thread to get directory listing in parallel.
    for(int i = 0; i < 16 && !dirs.empty(); ++i) {
      path dir = dirs.back();
      dirs.pop_back();
      future<result> ftr = std::async(std::launch::async, listDirectory,
			    dir);
      futures.push_back(std::move(ftr));
    }
    // wait for all 16 thread to finish.
    while(!futures.empty()) {
      auto ftr = std::move(futures.back());
      futures.pop_back();
      result res = ftr.get();
      std::copy(res.dirs.begin(), res.dirs.end(), back_inserter(dirs));
      std::copy(res.files.begin(), res.files.end(), back_inserter(files));   
    }
  }
  std::copy(files.begin(), files.end(),
	    std::ostream_iterator<path>(cout, "\n"));
  return 0;
}
