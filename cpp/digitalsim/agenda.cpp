#include <algorithm>
#include <iterator>
#include <iostream>

// our include files
#include <agenda.h>
#include <wire.h>

void AgendaItem::executeAgenda() {
  for_each(targets.begin(), targets.end(),
	   [](const AgendaObject &item) {
	     AgendaExecuter *obj = item.first;
	     void *args = item.second;
	     std::cout << "Executing on object " << obj << " with args " << args
		       << std::endl;
	     obj->executeAgenda(args);
	   });
}

// item to be executed.
AgendaItem* Agenda::getNext() {
  if (agendaQueue.empty())
    return NULL;
  else {
    AgendaQueue::iterator begin = agendaQueue.begin();
    agendaQueue.erase(agendaQueue.begin());
    return begin->second;
  }
  return NULL;
}

// Is there any agenda already registed.
AgendaItem* Agenda::findAgenda(unsigned long long time) {
  AgendaQueue::const_iterator item = agendaQueue.find(time);
  if (item == agendaQueue.end())
    return NULL;
  else
    return item->second;
}

// insert the future operaion on object at delay
void Agenda::insert(AgendaExecuter *obj, int delay, void *args) {
  AgendaItem *agendaItem  = findAgenda(current + delay);
  if (agendaItem == NULL) {
    agendaItem = new AgendaItem(current + delay);
    agendaQueue.insert(std::make_pair(current+delay, agendaItem));
  }
  agendaItem->insert(obj, args);
}

void Agenda::runSimulation() {
  // call stageChanged before starting the simulation
  // to schedule the events in agenda based on current
  // wire state.
  if (agendaQueue.empty()) {
    for_each(objects.begin(), objects.end(),
	     [](WireListner *obj) {
	       obj->stateChanged();
	     });
  }

  // Executes all pending events in agenda.
  AgendaItem *item = NULL;
  while ((item = getNext()) != NULL) {
    current = item->getTime();
    std::cout << "found an agenda to execute at " << current << std::endl;
    item->executeAgenda();
    delete item;
  }
}
