#ifndef _PATHQUEUESOUL_H_
  #define _PATHQUEUESOUL_H_

#include <queue>
#include <algorithm>
using std::max;
using std::queue;

#include "Soul.h"

class PathQueueSoul : public Soul {
private:
typedef V3D<float> v3f;
std::queue<v3f> targets;
v3f active_target;
int active = true;
Env* env;

public:
PathQueueSoul(Wagon* wagon, Env* env) : Soul(*wagon), env(env) {};

void add_target(v3f target) {
  targets.push(target);
}

void update() {
  capture_territories();

  if (active == false && !targets.empty()) {
    active_target.set(targets.front());
    targets.pop();
    active = true;
  }

  if ((wagon.pos - active_target).len() < 1.2) active = false;

  if (active) {
    auto ang2d = [] (v3f v) { return atan2(v.y, v.x); };
    auto diff_ang = (ang2d(active_target - wagon.pos) - ang2d(wagon.fd));
    diff_ang = fmod(diff_ang + 2 * M_PI, 2 * M_PI);
    float fd_fac = max(0., (M_PI/2 - fabs(diff_ang))) / M_PI;
    auto wvar = diff_ang / 10;

    // wagon.wheel_powers[0] = diff_ang < 0 ? f_p : 0;
    // wagon.wheel_powers[1] = diff_ang > 0 ? f_p : 0;
    wagon.wheel_powers[0] = fd_fac - wvar;
    wagon.wheel_powers[1] = fd_fac + wvar;
  } else {
    wagon.wheel_powers[0] = 0;
    wagon.wheel_powers[1] = 0;
  }
};

private:
void capture_territories() {
  // env->territories;
  // for (Territory* tr : (static_cast<RSim*>(wagon.env))->territories)
  //   if (tr->can_cap_wagon(*wagon))
  //     tr->owner = wagon;
}

};

#endif
