#ifndef NOTGATE_H
#define NOTGATE_H

#include <agenda.h>
extern Agenda agenda;

class NotGate : public WireListner {
private:
  Wire *in;
  Wire *out;
  unsigned long long delay;
 
public :
  NotGate(Wire *in, Wire *out) {
    this->in = in;
    this->out = out;
    delay = 1;
    in->addListner(this);

    agenda.addObject(this);
  }

  virtual void stateChanged() {
    if (in->get())
      agenda.insert(out, delay, (void*)0);
    else
      agenda.insert(out, delay, (void*)1);
  }
};

class TwoInputGate : public WireListner {
 public :
  Wire *in1;
  Wire *in2;
  Wire *out;
  int delay;
 private :
  virtual int calculateOutput() = 0;

 public :
 TwoInputGate(Wire *w1, Wire *w2, Wire *out):
  in1(w1), in2(w2), out(out) {
    agenda.addObject(this);
  }
  
  virtual void stateChanged() {
    bool newValue = calculateOutput();
    agenda.insert(out, delay, (void*)newValue);
  }
};

class AndGate : public TwoInputGate {
 private :
  virtual int calculateOutput() {
    return (in1->get() && in2->get()) ? 1 : 0;
  }
 public :
 AndGate(Wire *in1, Wire *in2, Wire *out) :
  TwoInputGate(in1, in2, out) {}
};

class OrGate : public TwoInputGate {
 private :
  virtual int calculateOutput() {
    return (in1->get() || in2->get()) ? 1 : 0;
  }
 public :
 OrGate(Wire *i1, Wire *i2, Wire *out) :
  TwoInputGate(i1, i2, out) {}
};

class XorGate : public TwoInputGate {
 private :
  virtual int calculateOutput() {
    int value = ((in1->get() && in2->get()) ||
	     (!in1->get() && !in2->get())) ? 0 : 1;
    return value;
  }
 public :
 XorGate(Wire *i1, Wire *i2, Wire *out) :
  TwoInputGate(i1, i2, out) {}

};

class NandGate : public TwoInputGate {
 private :
  virtual int calculateOutput() {
    return (in1->get() && in2->get()) ? 0 : 1;
  }
 public :
 NandGate(Wire *i1, Wire *i2, Wire *out) :
  TwoInputGate(i1, i2, out) {}
};

#endif

