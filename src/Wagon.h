#ifndef _WAGON_H_
  #define _WAGON_H_

#include "Orientable.h"

class Wagon : public Orientable {
private:
typedef V3D<float> v3f;

public:
float wheel_powers[2];
float color[3];
int n_balls = 0;
int max_balls = 10;

public:
Wagon(v3f pos) : Orientable(pos) {
  pitch(-M_PI/2);
  yaw(M_PI);

  wheel_powers[0] = 0;
  wheel_powers[1] = 0;

  auto rnd = [] () {return rand()/(float)RAND_MAX;};

  color[0] = rnd();
  color[1] = rnd();
  color[2] = rnd();
};

void update() {
  // translational position
  pos += fd * (wheel_powers[0] + wheel_powers[1]);

  // rotational position
  yaw((wheel_powers[0] - wheel_powers[1]) / 2);
};

};

#endif
