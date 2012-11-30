#ifndef _RSIM_H_
  #define _RSIM_H_

#include <iostream>
#include <vector>
using std::vector;
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Oggler.h"


class RSim {

private:

int running;
sf::Window* window;
Oggler cam;

public:

RSim();
int init();
void loop();
void event_handle();
void render_setup();
void render_pre();
void render();

};

#endif
