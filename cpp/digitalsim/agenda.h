#ifndef AGENDA_H
#define AGENDA_H

#include <utility>
#include <vector>
#include <map>
#include <set>

class WireListner;

class AgendaExecuter {
 public :
  virtual void executeAgenda(void *args) = 0;
};


class AgendaItem {
private :
  unsigned long long time; // time at which this agenda is to be
                           // executed.

  /* list of object who are registered a call back at this time */
  typedef std::pair<AgendaExecuter*, void*> AgendaObject;
  std::vector<AgendaObject> targets;

public :
  /* agenda is to be executed at time , time + agenda current time */
  AgendaItem(unsigned long long time): time(time) {}

  /* Add the object in the object list */
  void insert(AgendaExecuter *obj, void *args) {
    targets.push_back(std::make_pair(obj,args));
  }

  /* get time at which the Agenda to be executed */
  unsigned long long getTime() const { return time; }

  /* execute all the agenda */
  void executeAgenda();
};


/* A Agenda represents pending operations for simulations,
   It contains a list of agenda items */
class Agenda {
 private:
  typedef std::map<unsigned long long,AgendaItem*> AgendaQueue;
  AgendaQueue agendaQueue;

  unsigned long long current; // Current simulation time

  AgendaItem *getNext();
  AgendaItem *findAgenda(unsigned long long time);

  // Global list of objects
  std::set<WireListner*> objects;

 public:
  Agenda() { current = 0; }
  unsigned long long getCurrentTime() { return current; }
  void insert(AgendaExecuter *obj, int delay, void *args);
  void runSimulation();
  void addObject(WireListner *obj) { objects.insert(obj); }
};

#endif

