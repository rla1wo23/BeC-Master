#include <iostream>
using namespace std;

class Animal {
private:
  string name;

public:
  Animal() { cout << "Aniaml is created\n"; };
  virtual void sound() = 0;
  virtual ~Animal() {}
};

class Cat : public Animal {
public:
  Cat() { cout << "Cat is created\n"; };
  ~Cat() { cout << "meow bye\n"; }
  void sound() override { cout << "meow\n"; }
};
class Dog : public Animal {
public:
  ~Dog() { cout << "bye\n"; }
  void sound() override { cout << "grrrr\n"; };
};

int main() {
  Animal *animal1 = new Cat();
  Animal *animal2 = new Dog();
  animal1->sound();
  animal2->sound();
  delete animal1;
  delete animal2;
}