#include "rsim.h"

void RSim::render() {
  render_pre();

  // auto GLUQ = gluNewQuadric();

  // render souls
  for (auto soul : souls) {
    glPushMatrix();
      glTranslatef(soul->wagon->pos.x, soul->wagon->pos.y, soul->wagon->pos.z);
      glColor3f(1,1,1);
      glutSolidSphere(2, 16, 16);
    glPopMatrix();
  }

  // render targets
  for (auto target : targets) {
    glPushMatrix();
      glTranslatef(target->pos.x, target->pos.y, target->pos.z);
      glColor3f(1, 0.76, 0);
      glutSolidSphere(1, 16, 16);
    glPopMatrix();
  }


  window->display();
}
