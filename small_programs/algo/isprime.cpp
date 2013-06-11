#include <iostream>
#include <vector>

using namespace std;

bool fermat_test(unsigned long a, unsigned long p);
unsigned long a_raise_n_mod_p(unsigned long a, unsigned long b,
		      unsigned long p);

/*
 Algo: Select some random numbers less than p
 then do fermat test on them, if all of them
 passes fermat test then number is a prime
 with high confidence */
bool isprime(unsigned long p)
{
  return (fermat_test(2, p));
}

/* find out the fermat test for a and prime p */
/* a ** (p-1) == 1 (mod p) */
bool fermat_test(unsigned long a, unsigned long p)
{
  if (a_raise_n_mod_p(a, p-1, p) == 1)
    return true;
  else
    return false;
}

unsigned long a_raise_n_mod_p(unsigned long a, unsigned long n,
			       unsigned long p)
{
  unsigned long result = 1;
  unsigned long curr = a;
  /*
    check the bit position and multiply with the current
    value of a ** (2 ** n) mode p
    ** is the exponential operator :)
    invarients:
    curr is set to (a ** (2 ** i)) mod p for index i
  */
  for (int i = 0; i < 64; i++) {
    if (n & (1 << i))
      result = (result * curr) % p;
    curr = (curr * curr) % p;
  }
  return result;
}

int main(int argc, char **argv)
{
  unsigned long n;
  cin >> n;
  if (isprime(n))
    cout << n << " is prime \n";
  else
    cout << n << " is not prime \n";
  return 0;
}

