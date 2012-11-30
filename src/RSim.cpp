#include "rsim.h"

RSim::RSim() : running(true) {}

int RSim::init() {    
  //// initialize window
  sf::VideoMode desktop_mode = sf::VideoMode::getDesktopMode();
  sf::ContextSettings OGLContext(
    24, // depth
    8,  // stencil
    4,  // antialiasing
    2,  // major
    0); // minor
  window = new sf::Window(desktop_mode, "SFML Window", sf::Style::Fullscreen, OGLContext);

  // circles.push_back(new Orientable(v3f(0,0,0)));

  loop();

  return 0;
}

void RSim::loop() {
  render_setup();

  while(running) {
    event_handle();
    // step_physics();
    render();
  }
}

void RSim::event_handle() {
  // event loop
  sf::Event event;
  while (window->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        running = false;
        break;

      case sf::Event::Resized:
        glViewport(0, 0, event.size.width, event.size.height);
        break;

      case sf::Event::KeyPressed:
        switch (event.key.code) {
          case sf::Keyboard::Escape:
            running = false;
            break;

          default: break;
        }
        break;

      default: break;
    }
  }
}
