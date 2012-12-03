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

  Wagon* wagon = new Wagon(v3f(0,0,0));
  auto pqs = new PathQueueSoul(wagon);
  souls.push_back(pqs);

  targets.push_back(new Orientable(v3f(10, -30, 0)));
  targets.push_back(new Orientable(v3f(0, 50, 0)));
  targets.push_back(new Orientable(v3f(40, 3, 0)));
  targets.push_back(new Orientable(v3f(50, 2, 0)));
  targets.push_back(new Orientable(v3f(-30, 20, 0)));

  for ( auto tg : targets ) {
    pqs->add_target(tg->pos);
  }

  loop();

  return 0;
}

void RSim::loop() {
  render_setup();

  auto time_from = [] (sf::Clock& clk) {return clk.getElapsedTime().asMilliseconds();};

  clk.restart();
  sf::Clock phys_log_clk;
  sf::Clock render_clk;

  while(running) {
    event_handle();

    if (time_from(phys_log_clk) > 5) {
      physics_step();
      phys_log_clk.restart();
    }

    if (time_from(render_clk) > 6) {
      render();
      render_clk.restart();
    }

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
