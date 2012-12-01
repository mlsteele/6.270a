#include "rsim.h"

void RSim::render_setup() {
  // Color & Depth Clear Values
  glClearDepth(1.f);
  glClearColor(0.f, 0.f, 0.f, 0.f);

  // Z-buffer read and write
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  // Lighting
  GLfloat ambientcolor[] = {.6, .6, .6, 1};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);

  // Fog
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_EXP2);
  glFogf(GL_FOG_DENSITY, .005);
//  glFogi(GL_FOG_MODE, GL_LINEAR);
//  glFogf(GL_FOG_START, 40.f);
//  glFogf(GL_FOG_END, 100.f);
  float FogCol[3] = {0,0,0};
  glFogfv(GL_FOG_COLOR, FogCol);

  // // Lights
  // glEnable(GL_LIGHT0);
  //   light0pos[0] = 0; light0pos[1] = 0; light0pos[2] = 1; light0pos[3] = 1;
  //   light0dif[0] = .2; light0dif[1] = .2; light0dif[2] = .2; light0dif[3] = 1;
  //   glLightfv(GL_LIGHT0, GL_DIFFUSE, light0dif);
  // glEnable(GL_LIGHT1);
  //   light1pos[0] = 5; light1pos[1] = -2; light1pos[2] = 8; light1pos[3] = 1;
  //   light1dif[0] = .2; light1dif[1] = .2; light1dif[2] = .2; light1dif[3] = 1;
  //   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1dif);
  // glEnable(GL_LIGHT2);
  //   light2pos[0] = -2; light2pos[1] = 10; light2pos[2] = -1; light2pos[3] = 1;
  //   light2dif[0] = .2; light2dif[1] = .2; light2dif[2] = .2;  light2dif[3] = 1;
  //   glLightfv(GL_LIGHT2, GL_DIFFUSE, light2dif);
  // glEnable(GL_LIGHT3);
  //   light3pos[0] = -140; light3pos[1] = -110; light3pos[2] = 70; light3pos[3] = 1;
  //   light3dif[0] = .2; light3dif[1] = .2; light3dif[2] = .2;  light3dif[3] = 1;
  //   glLightfv(GL_LIGHT3, GL_DIFFUSE, light3dif);


  // point camera
  cam.settings(90, window->getSize().x / (float) window->getSize().y, .1, 500);
  cam.dolly->pos.z = 64;
  // cam.dolly->pitch(-M_PI/2.);
}

void RSim::render_pre() {
  // Enable Depth
  glEnable(GL_DEPTH_TEST);

  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Camera MODELVIEW & PERSPECTIVE Transformations
  cam.view_perspective();
  cam.view_model();

  // // Enable lighting & update light positions
  // glEnable(GL_LIGHTING);
  // glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  // glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
  // glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
}
