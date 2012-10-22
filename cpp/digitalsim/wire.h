#ifndef WIRE_H
#define WIRE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <agenda.h>
extern Agenda agenda;

class WireListner {
public :
  virtual void stateChanged() = 0;
};

class Wire : public AgendaExecuter {
private:
  bool signal;

  typedef std::vector<WireListner*> Listners;
  Listners listers;

public :
  Wire() {
    signal = false;
  }

  void addListner(WireListner *a) {
    listers.push_back(a);
  }

  bool get() { return signal; }

  void set(bool);

  virtual void executeAgenda(void *args)
  {
    bool newValue = (args == NULL)? false : true;
    set(newValue);
  }
};

#endif

