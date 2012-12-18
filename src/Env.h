#ifndef _ENV_H_
  #define _ENV_H_

#include "Territory.h"
#include "Wagon.h"

class Env {

public:
std::vector< Orientable* > targets;
std::vector< Territory* > territories;
std::vector< Wagon* > wagons;
};

#endif
