#include "rsim.h"

void RSim::render() {
  render_pre();

  // auto GLUQ = gluNewQuadric();

  for (auto wagon : wagons) {
    glPushMatrix();
      glTranslatef(wagon->pos.x, wagon->pos.y, wagon->pos.z);
      glColor3f(1,1,1);
      glutSolidSphere(2, 16, 16);
    glPopMatrix();
  }

  window->display();
}
