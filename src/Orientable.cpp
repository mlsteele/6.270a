#include "Orientable.h"

// constructor
// set to origin
Orientable::Orientable() {
  zero();
}

// zero
// zeros the camera in global space
void Orientable::zero() {
  pos.set(0, 0, 0);
  rt.set(1, 0, 0);
  up.set(0, 1, 0);
  fd.set(0, 0, -1);
}

// translateglobal
// translates the camera along the global space
void Orientable::translate_global(V3D<float> _offset) {
  pos.x += _offset.x;
  pos.y += _offset.y;
  pos.z += _offset.z;
}

// translatelocal
// translates the camera along local space
void Orientable::translate_local(V3D<float> _offset) {
  pos += rt * _offset.x;
  pos += up * _offset.y;
  pos += fd * _offset.z;
}

// pitch
// pitch the camera around up vector
void Orientable::pitch(float _theta) {
  up.spin_unit(_theta, rt);
  fd.spin_unit(_theta, rt);
}

// yaw
// yaw the camera around up vector
void Orientable::yaw(float _theta) {
  rt.spin_unit(_theta, up);
  fd.spin_unit(_theta, up);
}

// roll
// rolls the camera around forward vector
void Orientable::roll(float _theta) {
  up.spin_unit(_theta, fd);
  rt.spin_unit(_theta, fd);
}

// calibrate
// normalize camera axis
void Orientable::calibrate() {
  fd.normalize();
  rt.normalize();
  up.normalize();
}
