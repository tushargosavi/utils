#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <sequtils.h>

using namespace std;

template<typename OP1, typename OP2, typename OP3>
class compose_f_gx_hx_t
  : public std::unary_function<typename OP2::argument_type,
			       typename OP1::result_type>
{
private :
  OP1 op1;
  OP2 op2;
  OP3 op3;
public :
  compose_f_gx_hx_t(const OP1 &o1, const OP2 &o2, const OP3 &o3)
    :op1(o1), op2(o2), op3(o3) {
  }

  typename OP1::result_type
  operator() (const typename OP2::argument_type &x) {
    return op1( op2 (x) , op3(x) );
  }
};

/* helper function to create a class */
template<typename OP1,typename OP2,typename OP3>
inline compose_f_gx_hx_t<OP1,OP2,OP3>
compose_f_gx_hx(const OP1 &o1, const OP2 &o2, const OP3 &o3)
{
  return compose_f_gx_hx_t<OP1,OP2,OP3>(o1, o2, o3);
}

int main(int argc, char *argv[])
{
  vector<int> v1;
  populate_lseq(v1, 10);
  print_seq(v1, "v1 : ");
  
  /* remove elements which are greater than 4 and less than 7 */
  vector<int>::iterator pos = remove_if (v1.begin(), v1.end(),
		   compose_f_gx_hx( logical_and<bool>(),
				    bind2nd( greater<int>(), 4),
				    bind2nd( less<int>(), 7)));
  v1.erase(pos, v1.end());
  print_seq(v1, "v1 : ");
  return 0;
}
