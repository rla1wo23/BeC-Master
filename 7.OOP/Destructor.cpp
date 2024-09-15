#include <iostream>
using namespace std;
class A {
private:
  int *data1;

public:
  A() {
    cout << "class A\n";
    data1 = new int(10);
  };
  virtual ~A() {
    cout << "destructor A \n";
    delete data1;
  }
};
class B : public A {
private:
  int *data2;

public:
  B(int b) {
    cout << "class B\n";
    data2 = new int(b);
  }
  ~B() {
    cout << "If the virtual destructor did not exist, destructor B would never "
            "be "
            "called\n";
    cout << "destructor B \n";
    delete data2;
  }
};
int main() {
  A *Liskov = new B(10);
  delete Liskov;
}