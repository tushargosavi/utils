#include <iostream>
#include <sequtils.h>

using namespace std;

typedef vector<double> poly;

void insertzeros(poly &a, int n)
{
  for(int i = 0; i < n; ++i)
    a.push_back(0);
}

poly mult_poly(poly &a, poly &b)
{
  poly ret;

  // make polinomial of same size by
  // appending zeros
  int size = max(a.size(), b.size()) -1;
  size *= 2;
  insertzeros(a, size - a.size());
  insertzeros(b, size - b.size());

  // multiply polynomials
  for(int k = 0; k <= size; ++k) {
    double sum = 0;
    for (int i = 0; i <= k; ++i)
      sum += a[i] * b[k-i];
    ret.push_back(sum);
  }
  return ret;
}

poly add_poly(poly &a, poly &b)
{
  poly c;
  int size = max(a.size(), b.size());
  insertzeros(a, size - a.size());
  insertzeros(b, size - b.size());

  for (int i = 0; i < size; i++)
    c.push_back(a[i] + b[i]);
  return c;
}

int main(int argc, char **argv)
{
  poly a = { 1, 2, 3 };
  poly b = { 2, 1, 4 };
  poly c = mult_poly(a,b);
  poly add = add_poly(a,b);
  print_seq(a);
  print_seq(add);
  print_seq(c);
}
