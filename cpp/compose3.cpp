#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

/* somehow ptr_fun(toupper) is not working, hence
   I am forced to create a functional opbject to
   convert a char to uppercase */
class Upper : public std::unary_function<char, int>
{
public :
  Upper() { };
  int operator() (const char c)
  {
    if (c >= 'a' && c <= 'z')
      return c + ('A' - 'a');
    return c;
  }
};

/* implements f ( g(x), h(y) ) composition */
template<typename OP1, typename OP2, typename OP3>
class compose_f_gx_hy_t
  :public std::binary_function<typename OP2::argument_type,
			       typename OP3::argument_type,
			       typename OP1::result_type>
{
private :
  OP1 op1;
  OP2 op2;
  OP3 op3;
public :
  
  compose_f_gx_hy_t(const OP1 &o1, const OP2 &o2, const OP3 &o3)
    : op1(o1), op2(o2), op3(o3) {
  }

  typename OP1::result_type
  operator()(const typename OP2::argument_type &x,
	     const typename OP3::argument_type &y) {
    return op1 ( op2(x), op3(y) );
  }
};

/* helper function */
template<typename OP1, typename OP2, typename OP3>
inline compose_f_gx_hy_t<OP1,OP2,OP3>
compose_f_gx_hy(const OP1 &o1, const OP2 &o2, const OP3 &o3) {
  return compose_f_gx_hy_t<OP1,OP2,OP3>(o1, o2, o3);
}

int main(int argc, char *argv[])
{
  string s("Internationalization");
  string sub("Nation");

  string::iterator pos;
  pos = search(s.begin(), s.end(),
	       sub.begin(), sub.end(),
	       compose_f_gx_hy( equal_to<int>(),
				Upper(),
				Upper()));
  if (pos != s.end()) {
    cout << "\"" << sub << "\" is a part of \"" << s << "\" " << endl;
  }

  return 0;
}
