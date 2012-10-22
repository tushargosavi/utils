#ifndef ADDER_H
#define ADDER_H

#include <wire.h>
#include <simplegates.h>

class HalfAdder {
 public:

 HalfAdder(Wire *in1, Wire *in2, Wire *sum, Wire *carry) {
    new XorGate(in1, in2, sum);
    new AndGate(in1, in2, carry);
  };
};

class FullAdder {
 public :
  FullAdder(Wire *cin, Wire *in1, Wire *in2, Wire *sum, Wire *carry) {
    Wire *a = new Wire();
    Wire *b = new Wire();
    Wire *c = new Wire();
    new XorGate(in1, in2, a);
    new XorGate(a, cin, sum);
    new AndGate(a, cin, b);
    new AndGate(in1, in2, c);
    new OrGate(b, c, carry);
  }
};

#endif
