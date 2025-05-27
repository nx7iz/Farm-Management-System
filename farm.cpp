#include <iostream>
#include <cstdlib>
#include <ctime>
/*
  1. Water crops
  2. Work on worker classs
  3. Market option (buy / sell stocks)
*/
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
    cout << "\n"
         << name << " has been fed today. \n";
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
      cout << name << " is growing. Days left to harvest: " << daysToHarvest << endl;
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

void removeAnimal(int &animalCount, Animal *animals[])
{
  cout << "\nSelect animal to remove from (0 to " << animalCount - 1 << "): \n";
  for (int i = 0; i < animalCount; i++)
  {
    cout << i << ". " << animals[i]->getName() << "\n";
  }

  cout << "Enter choice: ";
  int removeIndex;
  cin >> removeIndex;

  if (removeIndex >= 0 && removeIndex < animalCount)
  {
    cout << animals[removeIndex]->getName() << " removed from the farm.\n";
    delete animals[removeIndex];
  }

  for (int i = removeIndex; i < animalCount - 1; i++)
  {
    animals[i] = animals[i + 1];
  }
  animalCount--;
}
void stimulateNewDay(int &animalCount, int &wheatDaysLeft, int &cornDaysLeft, Animal *animals[])
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

  if (wheatDaysLeft == 0)
    cout << "Wheat is ready to harvest\n";
  if (cornDaysLeft == 0)
    cout << "Corn is ready to harvest\n";
}
Animal *createAnimal(const int &index, const string &name)
{
  if (index == 1)
  {
    return new Cow(name);
  }
  else if (index == 2)
  {
    return new Chicken(name);
  }
  else
  {
    cout << "Invalid animal index.\n";
    return nullptr;
  }
}
void displayAnimalList(int &animalCount, Animal *animals[])
{
  cout << "\nAvailable Animals: "
       << animalCount << "\n";
  for (int i = 0; i < animalCount; i++)
    cout << i << ". " << animals[i]->getName() << "\n";
}
int getValidAnimalIndex(int &animalCount)
{
  int index;

  cout << "Enter the animal index: ";
  cin >> index;

  if (index < 0 || index >= animalCount)
  {
    cout << "Invalid index.\n";
    return -1;
  }
  return index;
}
bool checkAnimalValidity(int &animalCount)
{
  if (animalCount == 0)
  {
    cout << "No animals added yet.\n";
    return true;
  }
  return false;
}
int randomStocks()
{
  return 0;
}
int main()
{
  srand(time(0));

  const int maxAnimals = 10;
  Animal *animals[maxAnimals];
  int animalCount = 0;

  Wheat wheat;
  Corn corn;

  int wheatDaysLeft = -1;
  int cornDaysLeft = -1;
  int wheatStock = 0;
  int cornStock = 0;

  int choice;
  do
  {
    cout << "\n*** Welcome To Digital Farm Management System *** \n";
    cout << "1. Animal Management System \n";
    cout << "2. Crop Management System \n";
    cout << "3. Worker Management System \n";
    cout << "4. Check Stock Level \n";
    cout << "5. Go To Market \n";
    cout << "0. Exit \n";
    cout << "\nEnter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      do
      {
        cout << "\n*** Animal Management System *** \n";
        cout << "1. Add Animal \n";
        cout << "2. Produce Product \n";
        cout << "3. Feed Animal \n";
        cout << "4. Simulate New Day \n";
        cout << "5. Check Animal Health \n";
        cout << "6. View Animals \n";
        cout << "7. Remove Animal \n";
        cout << "0. Back \n";
        cout << "\nEnter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
          string name;
          int index;
          cout << "1. Cow \n2. Chicken \nEnter animal index: ";
          cin >> index;
          cout << "Enter animal name: ";
          cin >> name;
          Animal *newAnimal = createAnimal(index, name);
          if (newAnimal != nullptr)
            animals[animalCount++] = newAnimal;
          cout << name << " added.\n";
          break;
        }

        case 2:
        {
          if (checkAnimalValidity(animalCount))
            break;
          displayAnimalList(animalCount, animals);
          int index = getValidAnimalIndex(animalCount);
          if (index != -1)
            animals[index]->produce();
          break;
        }
        case 3:
        {
          if (checkAnimalValidity(animalCount))
            break;
          displayAnimalList(animalCount, animals);
          int index = getValidAnimalIndex(animalCount);
          if (index != -1)
            animals[index]->feed();
          break;
        }
        case 4:
          stimulateNewDay(animalCount, wheatDaysLeft, cornDaysLeft, animals);
          break;

        case 5:

          if (checkAnimalValidity(animalCount))
            break;
          for (int i = 0; i < animalCount; i++)
          {
            animals[i]->checkHealth();
          }
          break;

        case 6:
          displayAnimalList(animalCount, animals);
          break;

        case 7:
          if (checkAnimalValidity(animalCount))
            break;

          removeAnimal(animalCount, animals);
          break;

        case 0:
          break;

        default:
          cout << "Invalid choice. \n";
          break;
        }

      } while (choice != 0);

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
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
          wheat.grow();
          wheatDaysLeft = wheat.getDaysToHarvest();
          break;

        case 2:
          corn.grow();
          cornDaysLeft = corn.getDaysToHarvest();
          break;

        case 3:
          stimulateNewDay(animalCount, wheatDaysLeft, cornDaysLeft, animals);
          break;

        case 4:
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
              cout << "Wheat not ready or planted. Days left to harvest: " << wheatDaysLeft << "\n";
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
              cout << "Corn not ready or planted. Days left to harvest: " << cornDaysLeft << "\n";
            }
            else
            {
              cout << "Corn not ready or planted.\n";
            }
          }
          break;

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

    case 5:
    {
      int random = rand() % 35 + 20;
      // double unitRandom = 0.5 + rand() % (2.3 - 0.5 + 1);
      cout << "\nWelcome to THE MARKET... \n"
           << "Stocks refresh daily\n"
           << "Available Stocks\n"
           << "\n1. Corn stock:  " << random << " / per unit $" << unitRandom 
           << "\n2. Wheat stock: " << random << " / per unit $" << unitRandom
           << "\n3. Milk stock:  " << random << " / per unit $" << unitRandom
           << "\n4. Eggs stock:  " << random << " / per unit $" << unitRandom << endl;
      cout << "Enter stock index to buy: ";
      break;
    }
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
