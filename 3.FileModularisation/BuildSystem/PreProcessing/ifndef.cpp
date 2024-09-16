#include <iostream>

#ifndef DEBUG_MODE
#define LOG(msg)
#else
#define LOG(msg) std::cout << "DEBUG: " << msg << std::endl;
#endif

int main() {
  LOG("DEBUG MODE");
  std::cout << "The program ran fine." << std::endl;
  return 0;
}
