#include <iostream>
#include <boost/filesystem.hpp>

void listDirectory(boost::filesystem::path dir)
{
  try 
  {
    for(boost::filesystem::directory_iterator it(dir);
	it != boost::filesystem::directory_iterator();
	++it) {
      if (boost::filesystem::is_directory(it->status())) {
	std::cout << "directory " << it->path() << std::endl;
	listDirectory(it->path());
      }
      else
	std::cout << "file      " << it->path() << std::endl;
    }
  }
  catch (boost::filesystem::filesystem_error &e) 
  { 
    std::cerr << e.what() << std::endl; 
  }
}

int main(int argc, char **argv) 
{ 
  if (argc < 2) {
    std::cerr << "Usage " << argv[0] << " <directory>" << std::endl;
    return -1;
  }
  boost::filesystem::path p(argv[1]);
  listDirectory(p); 
}
