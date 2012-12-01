#ifndef _PATHQUEUESOUL_H_
  #define _PATHQUEUESOUL_H_

#include <queue>
using std::queue;

#include "Soul.h"

class PathQueueSoul : public Soul {
private:
typedef V3D<float> v3f;
std::queue<v3f> targets;
v3f active_target;
int active = true;

public:
PathQueueSoul(Wagon* wagon) : Soul(wagon) {};

void add_target(v3f target) {
  targets.push(target);
}

void update() {
  if (active == false && !targets.empty()) {
    active_target.set(targets.front());
    targets.pop();
    active = true;
  }

  if ((wagon->pos - active_target).len() < 1.2) active = false;

  if (active) {
    auto ang2d = [] (v3f v) { return atan2(v.y, v.x); };
    auto diff_ang = (ang2d(active_target - wagon->pos) - ang2d(wagon->fd));
    // auto pow_sum = (M_PI/2 - abs(diff_ang));
    auto f_p = 0.1;

    // std::cout << diff_ang << "\n";

    wagon->wheel_powers[0] = diff_ang < 0 ? f_p : 0;
    wagon->wheel_powers[1] = diff_ang > 0 ? f_p : 0;
  } else {
    wagon->wheel_powers[0] = 0;
    wagon->wheel_powers[1] = 0;
  }
};

};

#endif
