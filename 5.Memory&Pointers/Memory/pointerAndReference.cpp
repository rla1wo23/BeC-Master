#include <iostream>
void modifyWithPointer(int *ptr) { *ptr = 20; }
void modifyWithReference(int &ref) { ref = 30; }
int main() {
  int num = 10;
  int *ptr = &num;
  int &ref = num;
  std::cout << "ptr:" << ptr << " *ptr:" << *ptr << "\n";
  std::cout << "Value of ref:" << ref << std::endl;
  std::cout << "Original value of variable num : " << num << std::endl;
  modifyWithPointer(ptr);
  std::cout << "Modified value (using pointer): " << num << std::endl;
  modifyWithReference(ref);
  std::cout << "Modified value (using reference): " << ref << std::endl;
  return 0;
}