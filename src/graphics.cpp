#include "rsim.h"

void RSim::render() {
  render_pre();

  // auto GLUQ = gluNewQuadric();

  // render by souls
  for (auto soul : souls) {
    glPushMatrix();
      glTranslatef(soul->wagon->pos.x, soul->wagon->pos.y, soul->wagon->pos.z);
      glColor3f(soul->wagon->color[0], soul->wagon->color[1], soul->wagon->color[2]);
      glutSolidSphere(2, 16, 16);
    glPopMatrix();

    for (auto tr : territories) {
      tr->render();
      tr->contains_wagon(*(soul->wagon));
    }
  }

  // render targets
  for (auto target : targets) {
    glPushMatrix();
      glTranslatef(target->pos.x, target->pos.y, target->pos.z);
      glColor3f(1, 0.76, 0);
      glutSolidSphere(1, 16, 16);
    glPopMatrix();
  }

  auto time_from = [] (sf::Clock& clk) {return clk.getElapsedTime().asMilliseconds();};
  glColor3f(1,1,1);
  glPushMatrix();
    glTranslatef(43 * cos(time_from(clk) / 10000.), 40 * sin(time_from(clk) / 10000.), 0);
    glutSolidSphere(2, 16, 16);
  glPopMatrix();
  glPushMatrix();
    glRotatef(time_from(clk) / 10000. / M_PI * 180, 0, 0, 1);
    glTranslatef(50,0,0);
    glutSolidSphere(2, 16, 16);
  glPopMatrix();

  window->display();
}
