#include <iostream>

// definition of functions
int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int divide(int a, int b) {
  if (b != 0)
    return a / b;
  else {
    std::cerr << "Error: Division by zero!" << std::endl;
    return 0;
  }
}

// use call back function
void calculateAndPrint(int a, int b, int (*operation)(int, int)) {
  int result = operation(a, b);
  std::cout << "Result: " << result << std::endl;
}

int main() {
  int x = 10, y = 5;
  int choice;

  std::cout << "Choose operation: 1) Add 2) Subtract 3) Multiply 4) Divide: ";
  std::cin >> choice;

  switch (choice) {
  case 1:
    calculateAndPrint(x, y, add);
    break;
  case 2:
    calculateAndPrint(x, y, subtract);
    break;
  case 3:
    calculateAndPrint(x, y, multiply);
    break;
  case 4:
    calculateAndPrint(x, y, divide);
    break;
  default:
    std::cout << "Invalid choice!" << std::endl;
    break;
  }

  return 0;
}
