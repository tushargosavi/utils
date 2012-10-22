#include <iostream>

// our files
#include <wire.h>
#include <simplegates.h>
#include <probe.h>
#include <adder.h>

int main(int argc, char **argv)
{
  Wire *in1, *in2, *sum, *carry;
  in1 = new Wire();
  in2 = new Wire();
  sum = new Wire();
  carry = new Wire();

  HalfAdder* adr = new HalfAdder(in1, in2, sum, carry);
  //  new WireProbe(sum);
  //new WireProbe(carry);

  in1->set(true);
  in2->set(true);

  Wire *cin = new Wire();
  cin->set(true);
  Wire *fsum = new Wire();
  Wire *fcarry = new Wire();
  FullAdder *fadr = new FullAdder(in1, in2, cin, fsum, fcarry); 

  new WireProbe(fsum);
  new WireProbe(fcarry);

  agenda.runSimulation();
  return 0;
}
