#include <wire.h>

void Wire::set(bool value) {
  if (signal != value) {
    signal = value;
    for_each(listers.begin(), listers.end(),
	     [](WireListner *elm) {
	       elm->stateChanged();
	     });
  }
}

