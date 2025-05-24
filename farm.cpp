#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Animal
{
protected:
  string name;
  int health;
  bool fedToday;

public:
  Animal() {}

  Animal(string n) : name(n), health(100), fedToday(false) {}

  virtual void feed()
  {
    fedToday = true;
    cout << name << " has been fed today. \n";
    if (health < 100 && health > 0)
    {
      health += rand() % 12 + 4;
    }

    if (health > 100)
      health = 100;
  }

  virtual void newDay()
  {
    if (health != 0)
    {
      if (!fedToday)
      {
        int drop = rand() % 9 + 7;
        health -= drop;
        cout << "\n"
             << name << " was not fed today. Health decreased by " << drop << ".\n";
      }
      else
      {
        cout << name << " was well-fed today. Health remains stable. \n";
      }
    }

    fedToday = false;

    if (health == 0)
      cout << name << " died. Cause of death: Starvation.\n";
    else if (health < 50)
      cout << name << " Health is unstable. Please feed. \n";

    if (health < 0)
      health = 0;
  }

  virtual void checkHealth()
  {
    cout << "\n"
         << name << " has health: " << health << " /100\n";
  }

  virtual void produce()
  {
  }

  string getName() { return name; }
  // virtual ~Animal() {}
};

class Cow : public Animal
{
  bool milkProduced;
  static int milkCapacity;

public:
  Cow() {}

  Cow(string n) : Animal(n), milkProduced(false) {}

  void feed() override
  {
    Animal::feed();
    cout << "Fed cow " << name << " with hay. \n";
  }

  void newDay() override
  {
    Animal::newDay();
    milkProduced = false;
  }

  void produce() override
  {
    if (health > 55 && !milkProduced)
    {
      int random = rand() % 4 + 2;

      milkCapacity += random;

      cout << "\nCow is producing milk...\n";
      cout << name << " produced " << random << " liters of milk.\n";
      milkProduced = true;
    }
    else if (health < 55)
    {
      cout << "\nHealth not stable. Cannot produce milk. \n";
    }
    else
    {
      cout << name << " already produced milk.\n";
    }
  }

  void checkHealth() override
  {
    Animal::checkHealth();
    if (health < 50)
      cout << name << " health is unstable. Please feed. \n";
  }

  static int getMilkCapacity()
  {
    return milkCapacity;
  }
};

class Chicken : public Animal
{
  static int totalEggs;
  bool eggsLayed;

public:
  Chicken() {}

  Chicken(string n) : Animal(n), eggsLayed(false) {}

  void feed() override
  {
    Animal::feed();
    cout << "Chicken " << name << " has been fed with grains. \n";
  }

  void newDay() override
  {
    Animal::newDay();
    eggsLayed = false;
  }
  void produce() override
  {
    if (health > 55 && !eggsLayed)
    {
      int random = rand() % 5 + 1;

      totalEggs += random;

      cout << "\nChicken is laying eggs...\n";

      cout << random << " eggs layed.\n";
      eggsLayed = true;
    }
    else if (health < 55)
    {
      cout << "Health not stable. Cannot lay eggs. \n";
    }
    else
    {
      cout << name << " already layed eggs.\n";
    }
  }

  void checkHealth()
  {
    Animal::checkHealth();
    if (health < 50)
    {
      cout << "\n"
           << name << " health is unstable. Please feed\n";
    }
  }

  static int getTotalEggs()
  {
    return totalEggs;
  }
};

class Crop
{
protected:
  string name;
  int daysToHarvest;

public:
  Crop(string n = "", int days = 0) : name(n), daysToHarvest(days) {}

  virtual void grow()
  {
    cout << "Seed of " << name << " has been planted. Will grow soon.\n";
  }

  virtual void nextDay()
  {
    if (daysToHarvest > 0)
    {
      daysToHarvest--;
      cout << name << " is growing. Days left: " << daysToHarvest << endl;
    }
    else
    {
      cout << name << " is ready to harvest. \n";
    }
  }

  virtual int harvestYield()
  {
    return rand() % 11 + 10;
  }

  virtual void checkStatus()
  {
    cout << name << ": " << (daysToHarvest > 0 ? "Growing" : "Ready to harvest") << "(" << daysToHarvest << " days remaining)\n";
  }
  int getDaysToHarvest() { return daysToHarvest; }
};

class Wheat : public Crop
{
public:
  Wheat() : Crop("Wheat", 3) {}

  void grow() override
  {
    cout << "Planted wheat seeds.\n";
  }
  int harvestYield() override
  {
    return rand() % 18 + 8;
  }
};

class Corn : public Crop
{
public:
  Corn() : Crop("Corn", 4) {}

  void grow() override
  {
    cout << "Corn planted.\n";
  }
  int harvestYield() override
  {
    return rand() % 26 + 10;
  }
};

class Worker
{
public:
  virtual void performTask();
};

class AnimalCaretaker : public Worker
{
  void performTask() override
  {
  }
};

class FieldWorker : public Worker
{
  void performTask() override
  {
  }
};

int Cow::milkCapacity = 0;
int Chicken::totalEggs = 0;

int main()
{
  srand(time(0));

  const int maxAnimals = 10;
  Animal *animals[maxAnimals];
  int animalCount = 0;

  int cowIndices[10];
  int cowCount = 0;
  int chickenIndices[10];
  int chickenCount = 0;

  int wheatDaysLeft = -1;
  int cornDaysLeft = -1;
  int wheatStock = 0;
  int cornStock = 0;

  Wheat wheat;
  Corn corn;

  int choice;
  do
  {
    cout << "\n*** Welcome To DFMS *** \n";
    cout << "1. Animal Management System \n";
    cout << "2. Crop Management System \n";
    cout << "3. Worker Management System \n";
    cout << "4. Check Stock Level \n";
    cout << "0. Exit \n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:

      // // Crop

      // Animal
      do
      {
        cout << "\n*** Animal Management System *** \n";
        cout << "1. Add Cow \n";
        cout << "2. Produce Milk \n";
        cout << "3. Add Chicken \n";
        cout << "4. Lay Eggs \n";
        cout << "5. Feed Animal \n";
        cout << "6. Simulate New Day \n";
        cout << "7. Check Animal Health \n";
        cout << "8. Back \n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
          if (animalCount > maxAnimals)
          {
            cout << "Animal limit reached\n";
            break;
          }

          string name;

          cout << "Enter cow name: ";
          cin >> name;

          animals[animalCount] = new Cow(name);
          cowIndices[cowCount++] = animalCount;
          animalCount++;

          cout << name << " added.\n";

          break;
        }

        case 2:
        {
          if (cowCount == 0)
          {
            cout << "No cow to produce milk.\n";
            break;
          }

          for (int i = 0; i < cowCount; i++)
          {
            int index = cowIndices[i];
            Cow *cowPtr = (Cow *)animals[index];
            cowPtr->produce();
          }
          break;
        }
        case 3:
        {
          if (animalCount > maxAnimals)
          {
            cout << "Animal limit reached\n";
            break;
          }

          string name;

          cout << "Enter chicken name: ";
          cin >> name;

          animals[animalCount] = new Chicken(name);
          chickenIndices[chickenCount++] = animalCount;
          animalCount++;

          cout << name << " added.\n";
          break;
        }

        case 4:
        {
          if (chickenCount == 0)
          {
            cout << "\nNo chicken to lay eggs.\n";
            break;
          }

          for (int i = 0; i < chickenCount; i++)
          {
            int index = chickenIndices[i];
            Chicken *chickenPtr = (Chicken *)animals[index];
            chickenPtr->produce();
          }
          break;
        }
        case 5:
        {
          if (animalCount == 0)
          {
            cout << "No animals to feed. \n";
            break;
          }
          cout << "Select animal to feed (0 to " << animalCount - 1 << "): ";
          for (int i = 0; i < animalCount; i++)
          {
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
        case 6:
        {
          cout << "\nA new day has begun... \n";
          for (int i = 0; i < animalCount; i++)
          {
            animals[i]->newDay();
          }

          if (wheatDaysLeft > 0)
            wheatDaysLeft--;
          if (cornDaysLeft > 0)
            cornDaysLeft--;

          break;
        }
        case 7:
        {
          if (animalCount == 0)
          {
            cout << "No animals added yet. \n";
            break;
          }
          for (int i = 0; i < animalCount; i++)
          {
            animals[i]->checkHealth();
          }
          break;
        }
        case 8:
          break;

        default:
          cout << "Invalid choice. \n";
          break;
        }

      } while (choice != 8);

      break;

    case 2:

      do
      {
        cout << "\n*** Crop Management System *** \n";
        cout << "1. Plant Wheat\n";
        cout << "2. Plant Crop\n";
        cout << "3. Stimulate New Day\n";
        cout << "4. Harvest Crops\n";
        cout << "5. Back\n";
        cout << "Enter choice Farmer: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
          wheat.grow();
          wheatDaysLeft = wheat.getDaysToHarvest();
          break;
        }

        case 2:
        {
          corn.grow();
          cornDaysLeft = corn.getDaysToHarvest();
          break;
        }

        case 3:
        {
          if (wheatDaysLeft > 0)
            wheatDaysLeft--;
          if (cornDaysLeft > 0)
            cornDaysLeft--;

          cout << "\nA new day has begun... \n";
          for (int i = 0; i < animalCount; i++)
          {
            animals[i]->newDay();
          }
          if (wheatDaysLeft == 0)
            cout << "Wheat is ready to harvest\n";
          if (cornDaysLeft == 0)
            cout << "Corn is ready to harvest\n";
          break;
        }

        case 4:
        {
          if (wheatDaysLeft == 0)
          {
            int yield = wheat.harvestYield();
            wheatStock += yield;
            cout << "Wheat harvested! Yield: " << yield << " units.\n";
            wheatDaysLeft = -1;
          }
          else
          {
            if (wheatDaysLeft != -1)
            {
              cout << "Wheat not ready or planted. Days left: " << wheatDaysLeft << "\n";
            }
            else
            {
              cout << "Wheat not ready or planted.\n";
            }
          }

          if (cornDaysLeft == 0)
          {
            int yield = corn.harvestYield();
            cornStock += yield;
            cout << "Corn harvested! Yield: " << yield << " units.\n";
            cornDaysLeft = -1;
          }
          else
          {
            if (cornDaysLeft != -1)
            {
              cout << "Corn not ready or planted. Days left: " << cornDaysLeft << "\n";
            }
            else
            {
              cout << "Corn not ready or planted.\n";
            }
          }
          break;
        }

        case 5:
          break;

        default:
          cout << "Invalid choice\n";
          break;
        }
      } while (choice != 5);
      break;

    case 4:

      cout << "\nStock available\n";
      cout << "Milk capacity: " << Cow::getMilkCapacity() << endl;
      cout << "Total eggs: " << Chicken::getTotalEggs() << endl;

      cout << "\nCorn Stock: \n";
      cout << "Wheat stock: " << wheatStock << endl;
      cout << "Corn stock: " << cornStock << endl;
      break;

    case 0:
      cout << "Leaving Farm ...\n";
      break;

    default:
      cout << "Invalid Choice\n";
      break;
    }
  } while (choice != 0);

  for (int i = 0; i < animalCount; i++)
    delete animals[i];
}