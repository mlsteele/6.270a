#include "rsim.h"

RSim::RSim() : running(true) {}

int RSim::init() {
  // seed random
  srand(time(NULL));

  //// initialize window
  sf::VideoMode desktop_mode = sf::VideoMode::getDesktopMode();
  sf::ContextSettings OGLContext(
    24, // depth
    8,  // stencil
    4,  // antialiasing
    2,  // major
    0); // minor
  window = new sf::Window(desktop_mode, "SFML Window", sf::Style::Fullscreen, OGLContext);

  // setup wagon + soul
  for (int i = 0; i < 2; i++) {
    auto rnd = [] () {return rand()/(float)RAND_MAX;};
    // auto start_pos = (v3f(rand(), rand(), rand()) - v3f(0.5, 0.5, 0.5)) * 10;
    auto start_pos = (v3f(rnd(), rnd(), 0) - v3f(0.5, 0.5, 0)) * 10;
    start_pos.print();
    // auto start_pos = v3f(0,0,0);
    Wagon* wagon = new Wagon(start_pos);
    auto pqs = new IntuitSoul(wagon, &env);
    souls.push_back(pqs);
  }

  // create & load targets
  // env.targets.push_back(new Orientable(v3f(10, -30, 0)));
  // env.targets.push_back(new Orientable(v3f(0, 50, 0)));
  // env.targets.push_back(new Orientable(v3f(40, 3, 0)));
  // env.targets.push_back(new Orientable(v3f(50, 2, 0)));
  // env.targets.push_back(new Orientable(v3f(-30, 30, 0)));
  // env.targets.push_back(new Orientable(v3f(-10, -60, 0)));

  // for ( auto tg : env.targets ) {
  //   pqs->add_target(tg->pos);
  // }

  for (int i = 0; i < 6; i++) {
    auto angbuf = 0.1;
    env.territories.push_back(new Territory(v3f(0,0,0), i * M_PI / 3 - angbuf, (i + 1) * M_PI / 3 + angbuf));
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
