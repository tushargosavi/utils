#include <iostream>
#include <vector>
#include <algorithm>
#include <sequtils.h>
#include <functional>
#include <iterator>

using namespace std;

template <typename OP1, typename OP2>
class compose_f_gx_t
  :public std::unary_function<typename OP1::argument_type,
			      typename OP2::result_type>
{
private :
  OP1 op1;
  OP2 op2;
public :
  compose_f_gx_t(const OP1 &o1, const OP2 &o2)
    : op1(o1), op2(o2) {
  }

  typename OP1::result_type
  operator() (const typename OP1::argument_type& x) {
    return op1(op2(x));
  }
};

template <typename OP1, typename OP2>
inline compose_f_gx_t<OP1, OP2>
compose_f_gx(const OP1 &op1, const OP2 &op2) {
  return compose_f_gx_t<OP1,OP2>(op1, op2);
}

int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_lseq(v1, 9);
  print_seq(v1, "v1 : ");
  
  transform(v1.begin(), v1.end(),
	    ostream_iterator<int>(cout, " "),
	    compose_f_gx(bind2nd(multiplies<int>(), 5),
			 bind2nd(plus<int>(), 10)));
  cout << std::endl;
  return 0;
}
