#ifndef _WAGON_H_
  #define _WAGON_H_

#include "Orientable.h"

class Wagon : public Orientable {
private:
typedef V3D<float> v3f;

public:
float wheel_powers[2];

public:
Wagon(v3f pos) : Orientable(pos) {};
void update() {
  // translational position
  pos += fd * (wheel_powers[0] + wheel_powers[1]);

  // rotational position
  yaw((wheel_powers[0] + wheel_powers[1]) / 2);
};

};

#endif
