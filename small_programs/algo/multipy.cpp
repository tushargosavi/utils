#include <iostream>
#include <utility>

using namespace std;

int multiply(int a, int b)
{
  if (b == 0) return 0;
  int z = multiply(a, b/2);
  if (b % 2)
    return a+2*z;
  else
    return 2*z;
}

std::pair<int,int> divide(int x,int y)
{
  if (x == 0) return make_pair(0,0);
  std::pair<int,int> p = divide(x/2, y);
  int q = p.first;
  int r = p.second;
  q = 2 * q;
  r = 2 * r;
  if (x % 2)
    r++;
  if (r >= y) {
    r-=y;
    q++;
  }
  return make_pair(q,r);
}

int main(int argc, char **argv)
{
  int a;
  int b;

  cout << "Enter the numbers to multiply ";
  cin >> a;
  cin >> b;
  
  cout << "Result of mulitplication is " << multiply(a,b) << std::endl;
  std::pair<int,int> d = divide(a,b);
  cout << "Result of division is " << d.first << "  " << d.second << std::endl;
  
  return 0;
}
