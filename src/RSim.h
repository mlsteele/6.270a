#ifndef _RSIM_H_
  #define _RSIM_H_

#include <iostream>
#include <vector>
using std::vector;
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Env.h"
#include "Soul.h"
#include "IntuitSoul.h"
#include "Oggler.h"


class RSim {

private:
typedef V3D<float> v3f;

int running;
sf::Window* window;
sf::Clock clk;
Oggler cam;

std::vector< Soul* > souls;

Env env;


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
