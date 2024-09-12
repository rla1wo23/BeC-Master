#include <iostream>

class MyClass {
private:
  int data;
  mutable int accessCount; // mutable variable can changed in const function
  // It's keyword for compiler
public:
  MyClass(int d) : data(d), accessCount(0) {}

  int getData() const {
    accessCount++;
    return data;
  }

  int getAccessCount() const { return accessCount; }
};

int main() {
  const MyClass obj(10);

  std::cout << "Data: " << obj.getData() << std::endl;
  std::cout << "Access Count: " << obj.getAccessCount() << std::endl;

  return 0;
}
