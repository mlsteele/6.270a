#ifndef _SOUL_H_
  #define _SOUL_H_

#include "Wagon.h"
#include "RSim.h"

class Soul {
public:
Wagon* wagon;

public:
Soul(Wagon* wagon) : wagon(wagon) {};

virtual void update() = 0;
};

#endif
