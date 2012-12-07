#include "rsim.h"

void RSim::physics_step() {
  for (auto soul : souls) {
    soul->update();
    soul->wagon->update();

    // check ownership
    for (auto tr : territories) {
      if (tr->contains_wagon(*(soul->wagon)))
        tr->owner = soul->wagon;
      else
        tr->owner = NULL;
    }
  }  
}
