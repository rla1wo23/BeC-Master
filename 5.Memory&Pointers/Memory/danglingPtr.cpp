#include <iostream>

void dangling_ptr() {
  int *ptr = new int(10);
  std::cout << ptr << ":" << *ptr << "\n";
  delete ptr;
  ptr = nullptr;
  if (ptr != nullptr) {
    std::cout << ptr << "\n";
  } else {
    std::cout << "you guarded access to nullptr!\n";
  }
}
int main() { dangling_ptr(); }