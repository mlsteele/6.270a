#include <iostream>
#include "RSim.h"

int main(int argc, char** argv) {
  std::cout << "main\n";
  
  RSim app;
  int result = app.init();
  
  return result;
}
