#ifndef PROBE_H
#define PROBE_H

#include <agenda.h>

extern Agenda agenda;

class WireProbe : public WireListner {
 private :
  Wire *w;
  bool oldValue;

 public :
  WireProbe(Wire *w) {
    oldValue = w->get();
    this->w = w;
    w->addListner(this);
  }

  virtual void stateChanged() {
    bool value = w->get();
    std::cout << "state of wire " << w << " changed at "
	      << agenda.getCurrentTime() << " to " << (value? 1 : 0)
	      << std::endl;
  }
};

#endif
