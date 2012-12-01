#include "rsim.h"

void RSim::physics_step() {
  for (auto soul : souls) {
    soul->update();
    soul->wagon->update();
  }
}
