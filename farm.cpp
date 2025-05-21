#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Animal {
protected:
  string name;
  int age;
  int health;
  bool fedToday;

public:
  Animal(string n, int a) :
  name(n), age(a), health(100),fedToday(false) {}
  
  virtual void feed() {
    fedToday = true;
    cout << name << " has been fed today. \n";
    if (health < 100 && health > 0) {
      health += rand() % 9 + 1;
    }
    
    if (health > 100) health = 100;
    }

  virtual void newDay() {
    if (!fedToday) {
      int drop = rand() % 11 + 5;
      health -= drop;
      cout << name << " was not fed today. Health decreased by " << drop << ".\n";
    } else {
      cout << name << " was well-fed today. Health remains stable. \n";
    }

    fedToday = false;

    if (health < 0) health = 0;
  }

  virtual void checkHealth() {
    cout << name << " has health: " << health << " /100\n";
    // if (health < 40) {
    //   cout << name << " is at risk. Please feed. \n";
    // } else {
    //   cout << name << " is healthy\n";
    // }
  }
  string getName() { return name; }
  // virtual ~Animal() {}
};

class Cow: public Animal {
  int milkCapacity;
  bool milkProduced;

  public:
  Cow(string n, int a) : Animal(n, a), milkCapacity(0), milkProduced(false) {}

  void feed() override {
    Animal::feed();
    cout << "Fed cow " << name << " with hay. \n";
  }
  
  void newDay() override {
    Animal::newDay();
    milkProduced = false;  
  }
  
  void ProduceMilk() {
    if (health > 55 && !milkProduced) {
      milkCapacity += rand() % 5 + 1;
      milkProduced = true;
    } else if (health < 55) {
      cout << "Health not stable. Cannot produce milk. \n";
    } else {
      cout << "Milk already produced.\n";
    }
  }
  
  
  void checkHealth() override {
    cout << name << " has health: " << health << " /100\n";
    // if (health < 40) {
    //   cout << name << " is at risk of dying. Please feed. \n";
    // } else {
    //   cout << name << " is healthy\n";
    // }
  }
};

class Chicken: public Animal {
  int totalEggs;
  bool eggsLayed;
public:
  Chicken(string n, int a) : Animal(n, a), totalEggs(0), eggsLayed(false) {}

  void feed() override {
    Animal::feed();
    cout << "Chicken " << name << " has been fed with grains. \n";
  }

  void newDay() override {
    Animal::newDay();
    eggsLayed = false;
  }
  void layEggs() {
    if (health > 55 && !eggsLayed) {
      totalEggs += rand() % 5 + 1;
      eggsLayed = true;
    } else if (health < 55) {
      cout << "Health not stable. Cannot lay eggs. \n";
    } else {
      cout << "Eggs already layed.\n";
    }
  }

  void checkHealth() {
    cout << name << " has health: " << health << " /100\n";

  }
};

class Crop {
protected:
  string name;
  int daysToHarvest;
public:
  virtual void grow();
};

class Wheat : public Crop {

};

class Corn : public Crop {

};

class Worker {
public:
  virtual void performTask();
};

class AnimalCaretaker : public Worker {
  void performTask() override {
    
  }
};

class FieldWorker : public Worker {
  void performTask() override {

  }
};

int main() {
  srand(time(0));

  const int maxAnimals = 10;
  Animal* animals[maxAnimals];
  int animalCount = 0;

  int choice;
  do {
    cout << "\n*** Welcome To DFMS *** \n";
    cout << "1. Add Cow \n";
    cout << "2. Add Chicken \n";
    cout << "3. Feed Animal \n";
    cout << "4. Simulate New Day \n";
    cout << "5. Check Animal Health \n";
    cout << "0. Exit \n";
    cout << "Enter your choice: ";

    cin >> choice;

    switch(choice) {
      case 1: {
        if (animalCount > maxAnimals) {
          cout << "Animal limit reached\n";
          break;
        }
        string name;
        int age;
        cout << "Enter cow name and age: ";
        cin >> name >> age;
        animals[animalCount++] = new Cow(name, age);
        cout << name << " added as " << animalCount << ".\n";
        break;
      }
      case 2: {
        if (animalCount > maxAnimals) {
          cout << "Animal limit reached\n";
          break;
        }
        string name;
        int age;
        cout << "Enter chicken name and age: ";
        cin >> name >> age;
        animals[animalCount++] = new Chicken(name, age);
        cout << name << " added as " << animalCount << ".\n";
        break;
      }
      case 3: {
        if (animalCount == 0) {
          cout << "No animals to feed. \n";
          break;
        }
        cout << "Select animal to feed (0 to " << animalCount - 1 << "): ";
        for (int i = 0; i < animalCount; i++) {
          cout << i << ". " << animals[i]->getName() << " \n";
        }
        int idx;
        cin >> idx;
        if (idx >= 0 && idx < animalCount)
          animals[idx]->feed();
        else 
          cout << "Invalid Index!\n";
        break;
      }
      case 4: {
        cout << "A new day has begun... \n";
        for (int i = 0; i < animalCount; i++) {
          animals[i]->newDay();
        }
        break;
      }
      case 5: {
        if (animalCount == 0) {
          cout << "No animals added yet. \n";
          break;
        }
        for (int i = 0; i < animalCount; i++) {
          animals[i]->checkHealth();
        }
        break;
      }
      case 0: {
        cout << "Exiting program...\n";
        break;
      }
      default: 
        cout << "Invalid choice. \n";
    }

  } while (choice != 0);

  for (int i = 0; i < animalCount; i++) 
    delete animals[i];
}