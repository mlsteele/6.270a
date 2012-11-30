#include "Oggler.h"

Oggler::Oggler() {
  dolly = new Orientable();
  own_dolly = true;
  fov = 90;
  aspect = 4/3;
  near = 1;
  far = 500;
}

Oggler::Oggler(Orientable* _dolly) {
  dolly = _dolly;
  own_dolly = false;
  fov = 90;
  aspect = 4/3;
  near = 1;
  far = 500;
}

// Settings
// Camera settings
void Oggler::settings(float _fov, float _aspect, float _near, float _far) {
  fov = _fov;
  aspect = _aspect;
  near = _near;
  far = _far;
}

// Attach
// Attach camera to an orientable
void Oggler::attach(Orientable* _dolly) {
  if (own_dolly) {
    delete dolly;
  }
  
  dolly = _dolly;
  own_dolly = false;
}

// View
// Applies openGL transformations to MODLELVIEW and PERSPECTIVE
void Oggler::view_model() {
  // Modelview Setup
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
    dolly->pos.x, dolly->pos.y, dolly->pos.z,
    dolly->pos.x + dolly->fd.x, dolly->pos.y + dolly->fd.y, dolly->pos.z + dolly->fd.z,
    dolly->up.x, dolly->up.y, dolly->up.z
  );
}

void Oggler::view_perspective() {
  // Perspective Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, aspect, near, far);
  glMatrixMode(GL_MODELVIEW);
}