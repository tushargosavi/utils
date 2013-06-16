#include <iostream>
#include <iterator>
#include <boost/filesystem.hpp>

void listContents(boost::filesystem::path dir)
{
  if (!boost::filesystem::exists(dir))
    return;
  for(boost::filesystem::directory_iterator iter(dir);
      iter != boost::filesystem::directory_iterator();
	++iter) {
    //   if (iter->is_directory())
    //  listContents(iter->path());
    //else
    std::cout << "filename " << iter->path()->leaf();
  }
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage " << argv[0] << " directory" << std::endl;
    return -1;
  }

  boost::filesystem::path dir(std::string(argv[1]));
  listContents(dir);

  return 0;
}
