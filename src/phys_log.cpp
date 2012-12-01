#include "rsim.h"

void RSim::physics_step() {
  for (auto wagon : wagons) {
    wagon->pos.x += 0.0001;
  }
}
