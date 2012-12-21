#ifndef _INTUITSOUL_H_
  #define _INTUITSOUL_H_

#include <list>
#include <algorithm>
using std::max;
using std::list;

#include "Soul.h"

class IntuitSoul : public Soul {
private:
typedef V3D<float> v3f;
Env* env;
v3f target;
int target_active = true;

public:
IntuitSoul(Wagon* wagon, Env* env) : Soul(*wagon), env(env) {};

void update() {
  decide();
  if (target_active) locomote();
};

private:
void locomote() {
  if ((wagon.pos - target).len() < 1.2) target_active = false;

  if (target_active) {
    auto ang2d = [] (v3f v) { return atan2(v.y, v.x); };
    auto diff_ang = (ang2d(target - wagon.pos) - ang2d(wagon.fd));
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

void decide() {
  auto atr = at_disp_post();

  // auto-capture territories
  for (auto tr : env->territories) {
    if (tr->at_cap_post(wagon)) tr->capture(wagon);
  }

  if (at_disp_post() != NULL && wagon.n_balls < wagon.max_balls && !atr->is_empty()) { // should collect
    atr->ask_for_ball(wagon);
    std::cout << "n_balls: " << wagon.n_balls << "\n";
  } else if (wagon.n_balls == wagon.max_balls) { // should dump
    target = v3f(0,0,0);
    target_active = true;
    if ((wagon.pos - v3f(0,0,0)).len() < 6) {
      wagon.n_balls = 0;
    }
  } else { // should wander
    find_closest_objective();
  }
};

Territory* at_disp_post() {
  for (auto tr : env->territories) {
    if (tr->at_disp_post(wagon))
      return tr;
  }
  return NULL;
}

void find_closest_objective() {
  list<v3f> objvs_disp;
  list<v3f> objvs_cap;

  for (auto tr : env->territories) {
    if (tr->owner == &wagon)
      objvs_disp.push_back(tr->disp_pos());
    else // TODO: test for emptiness.
      objvs_cap.push_back(tr->cap_pos());
  }

  if (!objvs_cap.empty())
    target = closest_pos(objvs_cap);
  else
    target = closest_pos(objvs_disp);

  target_active = true;
};

v3f& closest_pos(list<v3f>& ps) {
  v3f closest = ps.front();
  for (auto p : ps) {
    if ((p - wagon.pos).len() < (closest - wagon.pos).len())
      closest = p;
  }
  return closest;
}

};

#endif
