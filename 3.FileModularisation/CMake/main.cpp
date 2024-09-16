#include "math_operations.h"
#include <iostream>

int main() {
  std::cout << "input two integers:";
  int a, b;
  std::cin >> a >> b;
  Calculator c = Calculator(a, b);
  std::cout << "Result of add two integers :" << c.add() << "\n";
  std::cout << "Result of subtract two integers :" << c.subtract() << "\n";
}