#include <iostream>

#define T1 // If you want to know how this code works, comment out this part.
class test1 {
public:
  virtual void print() { std::cout << "T1 is not Defined\n"; }
};

#ifdef T1 // if T1 defined, then below this codes could be ran
class test2 : public test1 {
public:
  void print() override { std::cout << "T1 is Defined\n"; }
};
#else
// If T1 is undefined, test2 behaves the same as test1.
typedef test1 test2;
#endif

int main() {
  test2 obj;
  obj.print();
  return 0;
}
