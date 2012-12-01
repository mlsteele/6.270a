#ifndef _RSIM_H_
  #define _RSIM_H_

#include <iostream>
#include <vector>
using std::vector;
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Wagon.h"
#include "Soul.h"
#include "PathQueueSoul.h"
#include "Oggler.h"


class RSim {

private:

typedef V3D<float> v3f;

int running;
sf::Window* window;
Oggler cam;

std::vector< Soul* > souls;
std::vector< Orientable* > targets;

public:

RSim();
int init();
void loop();
void event_handle();
void physics_step();
void render_setup();
void render_pre();
void render();

};

#endif
