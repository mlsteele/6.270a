#ifndef _TERRITORY_H_
  #define _TERRITORY_H_

#include "V3D.h"
#include "Orientable.h"
#include "Wagon.h"

class Territory : public Orientable {
private:
typedef V3D<float> v3f;

public:
v3f pos;
float rad_in = 15;
float rad_out = 40;
float rad_cap;
float rad_disp;
float theta_0;
float theta_1;
float theta_cap;
float theta_disp;

Wagon* owner = NULL;

public:

Territory(v3f _pos, float _theta_0, float _theta_1) : Orientable(_pos) {
  pitch(-M_PI/2);
  yaw((_theta_0 + _theta_0) / 2.);
  theta_0 = _theta_0;
  theta_1 = _theta_1;

  auto fr_th = [&] (float fr) {return fr * (theta_1 - theta_0) + theta_0;};
  theta_cap = fr_th(0.23);
  theta_disp = fr_th(0.8);
  rad_cap = rad_out * 0.9;
  rad_disp = rad_out * 0.9;
};

void capture(Wagon& wagon) {
  owner = &wagon;
}

void render() {
  auto quad = gluNewQuadric();
  glPushMatrix();
  glTranslatef(pos.x, pos.y, pos.z);

  // render slice
  // void gluPartialDisk(quad, inner, outer, slices, loops, start, sweep)
  glColor3f(.8, .8, .8);
  glPushMatrix();
    glRotatef(180, 1, 1, 0);
    gluPartialDisk(quad, rad_in, rad_out, 64 * (theta_1 - theta_0) / 2 / M_PI, 3, theta_0 / M_PI * 180, (theta_1 - theta_0) / M_PI * 180);
  glPopMatrix();

  // owner indicator
  glColor3f(1, 1, 1);
  if (owner != NULL) glColor3f(owner->color[0], owner->color[1], owner->color[2]);
  glPushMatrix();
    glTranslatef(0,0,1);
    glRotatef(180, 1, 1, 0);
    gluPartialDisk(quad,
      (rad_out - rad_in) / 3 + rad_in,
      (rad_out - rad_in) * 2 / 3 + rad_in,
      64 * (theta_1 - theta_0) / 2 / M_PI, 3,
      (theta_0 + (theta_1 - theta_0) / 3.) / M_PI * 180,
      ((theta_1 - theta_0) / 3.) / M_PI * 180 );
  glPopMatrix();

  // capture point
  glColor3f(0.9, 0.4, 0.4);
  glPushMatrix();
    glRotatef(theta_cap / M_PI * 180, 0, 0, 1);
    glTranslatef(rad_cap, 0, 0);
    glutSolidSphere(1, 16, 16);
  glPopMatrix();

  // dispenser
  glColor3f(0.4, 0.4, 0.9);
  glPushMatrix();
    glRotatef(theta_disp / M_PI * 180, 0, 0, 1);
    glTranslatef(rad_disp, 0, 0);
    glutSolidSphere(1, 16, 16);
  glPopMatrix();

  // render indicator
  glPopMatrix();
  gluDeleteQuadric(quad);
};

int contains_wagon(Wagon& w) {
  auto ang2d = [] (v3f v) { return atan2(v.y, v.x); };
  auto dr = (w.pos - pos).len();
  auto an = fmod(ang2d(w.pos - pos) + 2 * M_PI, 2 * M_PI);
  auto s_theta_0 = fmod(theta_0, 2 * M_PI);
  auto s_theta_1 = fmod(theta_1, 2 * M_PI);

  return (s_theta_0 < an) && (an < s_theta_1) && (rad_in < dr) && (dr < rad_out);
}

int can_cap_wagon(Wagon& w) {
  return (cap_pos() - w.pos).len() < 6;
}

v3f cap_pos() {
  return pos + v3f(cos(theta_cap), sin(theta_cap), 0) * rad_cap;
}

};

#endif
