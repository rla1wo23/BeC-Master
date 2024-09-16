// main.cpp
#include "my_header.h"
#include <iostream>

int main() {
#ifdef USE_MYFUNCTION
  myFunction(); // if use_myfunction defined then run this code
#else
  std::cout << "myFunction을 사용할 수 없습니다." << std::endl;
#endif
  return 0;
}
