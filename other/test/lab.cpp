#include <iostream>

using namespace std;

class Animal {
public:
  virtual void makeSound() {
    cout << "making sound\n";
  }
  void eat() {

  }
};

class Dog : public Animal {
public:
  void makeSound() override {
    cout << "Bark\n";
  }
};

class Cat : public Animal {
public:
  void makeSound() override {
    cout << "Meow\n";
  }
};

class Bird : public Animal {
public:
  void makeSound() override {
    cout << "Chirp\n";
  }
};

int main() {
  Animal* arr[3];
  Dog d1;

  // Animal* ptr = new Dog;
  // Animal* ptr = &d1;
  
  Cat c1;
  Bird b1;

  arr[0] = new Dog();
  arr[1] = new Cat();
  arr[2] = new Bird();

  // arr[0] = &d1;
  // arr[1] = &c1;
  // arr[2] = &b1;

  for (int i = 0; i < 3; i++) {
    arr[i]->makeSound();
    arr[i]->eat();
  }

}