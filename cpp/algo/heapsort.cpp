#include <heap.h>
#include <sequtils.h>

int main(int argc, char **argv)
{
  std::vector<int> data;
  populate_rand(data, 100);

  // sort in small to large order
  std::vector<int> asc;
  Heap<int> h1(data);
  while(!h1.empty()) {
    asc.push_back(h1.remove());
  }

  // sort in large to small order
  std::vector<int> desc;
  Heap<int, std::greater<int>> h2(data);
  while(!h2.empty()) {
    desc.push_back(h2.remove());
  }

  print_seq(asc);
  print_seq(desc);
  std::cout << "is sorted " << is_sorted_seq(asc) << std::endl;
}
