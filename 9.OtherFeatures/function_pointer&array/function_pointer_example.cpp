#include <iostream>

// calculating
int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int divide(int a, int b) {
  if (b != 0)
    return a / b;
  else
    std::cerr << "Error: Division by zero!" << std::endl;
  return 0;
}

int main() {
  // definition of pointer
  int (*operation)(int, int);
  // int: return type, *operation: name of function pointer, (int, int):
  // parameters

  // operators
  operation = &add; // var operation holds function add's address
  std::cout << "Addition of 10 and 5: " << operation(10, 5) << std::endl;

  operation = &subtract; // var operation holds function subtract's address
  std::cout << "Subtraction of 10 and 5: " << operation(10, 5) << std::endl;

  operation = &multiply;
  std::cout << "Multiplication of 10 and 5: " << operation(10, 5) << std::endl;

  operation = &divide;
  std::cout << "Division of 10 by 5: " << operation(10, 5) << std::endl;
  int (*operations[])(int, int) = {add, subtract, multiply, divide};
  for (int i = 0; i < 4; i++) {
    std::cout << "operation" << i << " of 10 and 5: " << operations[i](10, 5)
              << "\n";
  }
  return 0;
}