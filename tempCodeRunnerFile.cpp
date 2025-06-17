#include <iostream>
#include <cstdlib>
#include <ctime>
/*
  1. Water crops
  2. Work on worker classs
  3. Market choice (buy / sell stocks)
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
  static void addMilk(int qty) { milkCapacity += qty; }
  static void removeMilk(int qty) { milkCapacity = max(0, milkCapacity - qty); }
};

class Chicken : public Animal
{
  static int totalEggs;
  bool eggsLaid;

public:
  Chicken() {}

  Chicken(string n) : Animal(n), eggsLaid(false) {}

  void feed() override
  {
    Animal::feed();
    cout << "Chicken " << name << " has been fed with grains. \n";
  }

  void newDay() override
  {
    Animal::newDay();
    eggsLaid = false;
  }
  void produce() override
  {
    if (health > 55 && !eggsLaid)
    {
      int random = rand() % 5 + 1;

      totalEggs += random;

      cout << "\nChicken is laying eggs...\n";

      cout << random << " eggs laid.\n";
      eggsLaid = true;
    }
    else if (health < 55)
    {
      cout << "Health not stable. Cannot lay eggs. \n";
    }
    else
    {
      cout << name << " already laid eggs.\n";
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

  static int getTotalEggs() { return totalEggs; }
  static void addEgg(int qty) { totalEggs += qty; }
  static void removeEgg(int qty) { totalEggs = max(0, totalEggs - qty); }
};

class AnimalManager
{
private:
  Animal *animals[10];
  int animalCount;
  int index;
  string name;

public:
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
};

class Crop
{
protected:
  string name;
  int daysToHarvest;
  bool isWatered;

public:
  Crop(string n = "") : name(n), isWatered(false), daysToHarvest(-1) {}

  virtual void grow()
  {
    cout << "Seed of " << name << " has been planted. Will grow soon.\n";
  }

  virtual void water()
  {
    isWatered = true;
    cout << "Watering " << name << "...\n";
  }

  virtual void newDay()
  {
    if (daysToHarvest != 0)
    {
      if (daysToHarvest != -1)
      {
        if (daysToHarvest <= 2 && !isWatered)
          cout << name << " needs to be watered\n";
        else if (daysToHarvest > 0)
        {
          daysToHarvest--;
          if (daysToHarvest > 0)
            cout << name << " is growing. Days left to harvest: " << daysToHarvest << endl;
        }
      }
    }
    if (daysToHarvest == 0)
      cout << name << " is ready to harvest\n";
    isWatered = false;
  }

  virtual int harvestYield()
  {
    return rand() % 11 + 10;
  }

  int getDaysToHarvest() { return daysToHarvest; }
  void setDaysToHarvest(int days) { daysToHarvest = days; }

  virtual void checkStatus()
  {
    if (daysToHarvest != -1)
      cout << name << " Status: " << (daysToHarvest > 0 ? "Growing" : "Ready to harvest") << "(" << daysToHarvest << " days remaining)\n";
    else
      cout << name << " Status: not planted yet.\n";
  }

  bool getIsWatered() { return isWatered; }
};

class Wheat : public Crop
{

public:
  Wheat() : Crop("Wheat") {}

  void grow() override
  {
    daysToHarvest = 3;
    cout << "Planted wheat seeds.\n";
  }
  void newDay() override
  {
    Crop::newDay();
  }

  int harvestYield() override
  {
    if (isWatered || daysToHarvest == 0)
      return rand() % 26 + 10;
    else
      cout << "Wheat not watered. Please water.\n";
    return 0;
  }

  void water() override
  {
    if (daysToHarvest != -1)
      Crop::water();
    else
      cout << name << " not planted yet.\n";
  }
};

class Corn : public Crop
{
public:
  Corn() : Crop("Corn") {}

  void grow() override
  {
    daysToHarvest = 4;
    cout << "Corn planted.\n";
  }
  void newDay() override
  {
    Crop::newDay();
  }
  int harvestYield() override
  {
    if (isWatered || daysToHarvest == 0)
    {
      return rand() % 26 + 10;
      isWatered = false;
    }
    else
      cout << "Corn not watered. Please water.\n";
    return 0;
  }

  void water() override
  {
    if (daysToHarvest != -1)
      Crop::water();
    else
      cout << name << " not planted yet.\n";
  }
};

class Worker
{
public:
  virtual void performTask();
};

void stimulateNewDay(int &animalCount, Animal *animals[], Wheat *wheat, Corn *corn)
{
  cout << "\nA new day has begun... \n";
  for (int i = 0; i < animalCount; i++)
  {
    animals[i]->newDay();
  }

  wheat->newDay();
  corn->newDay();
}

bool checkQuantity(int &quantity, const int &stock)
{
  if (quantity > stock)
  {
    cout << "\nError! Cannot process, Stock seems to be low.\n";
    return true;
  }
  return false;
}
void buyStock(double &balance, int &stock, int &quantity, double &value)
{
  if (value > balance)
  {
    cout << "Not enough balance to buy.\n";
  }
  else if (balance > 0)
  {
    stock += quantity;
    balance -= value;
    cout << "Purchased " << quantity << " units/liters for $" << value << "\n";
  }
}
double getValue(int &quantity, double &stock)
{
  return (quantity * stock) / 2;
}
int getStock()
{
  return rand() % 35 + 20;
}
double getUnit()
{
  return (rand() % 3 + 1.0) / 2;
}
void showAvailableStock(int milkStock, int eggStock, int &wheatStock, int &cornStock)
{
  cout << "\nCurrently Available Stocks"
       << "\n1. Corn:  " << cornStock << " Units"
       << "\n2. Eggs:  " << eggStock << " Units"
       << "\n3. Milk:  " << milkStock << " Liters"
       << "\n4. Wheat: " << wheatStock << " Units" << "\n";
}

void sellStock(double &balance, int &stock, int &quantity, double &value)
{
  stock -= quantity;
  balance += value;
  cout << quantity << " units/liters sold. $" << value << " earned!!\n";
}

void harvestCrops(Crop *crop, int &stock, string name)
{
  if (crop->getDaysToHarvest() == 0)
  {
    int yield = crop->harvestYield();
    stock += yield;
    cout << name << " harvested! Yield: " << yield << " units.\n";
    crop->setDaysToHarvest(-1);
  }
  else
  {
    crop->checkStatus();
  }
}

int Cow::milkCapacity = 0;
int Chicken::totalEggs = 0;
// int Crop::daysToHarvest = -1;

int main()
{
  srand(time(0));

  AnimalManager animalManager;
  Crop crop;
  Wheat wheat;
  Corn corn;

  const int maxAnimals = 10;
  Animal *animals[maxAnimals];
  int animalCount = 0;

  int stock;
  double balance = 10.00;
  int wheatDaysLeft = -1;
  int cornDaysLeft = -1;
  int wheatStock = 0;
  int cornStock = 0;

  int choice;
  do
  {
    cout << "\n*** Welcome To Digital Farm Management System *** \n"
         << "1. Animal Management System \n"
         << "2. Crop Management System \n"
         << "3. Worker Management System \n"
         << "4. Stimulate New Day \n"
         << "5. Check Stock Level \n"
         << "6. Go To Market \n"
         << "0. Exit \n"
         << "\nEnter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      do
      {
        cout << "\n*** Animal Management System *** \n"
             << "1. Add Animal \n"
             << "2. View Animals \n"
             << "3. Remove Animal \n"
             << "4. Back \n"
             << "\nEnter your choice: ";

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
          Animal *newAnimal = animalManager.createAnimal(index, name);
          if (newAnimal != nullptr)
            animals[animalCount++] = newAnimal;
          cout << name << " added.\n";
          break;
        }

        case 2:
          animalManager.displayAnimalList(animalCount, animals);
          break;

        case 3:
          if (animalManager.checkAnimalValidity(animalCount))
            break;

          animalManager.removeAnimal(animalCount, animals);
          break;

        case 4:
          break;

        default:
          cout << "Invalid choice. \n";
          break;
        }

      } while (choice != 4);
      break;

    case 2:

      do
      {
        cout << "\n*** Crop Management System *** \n"
             << "1. Plant Wheat\n"
             << "2. Plant Crop\n"
             << "3. Harvest Crops\n"
             << "4. Back\n"
             << "\nEnter your choice: ";
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
          harvestCrops(&wheat, wheatStock, "Wheat");
          harvestCrops(&corn, cornStock, "Corn");
          break;

        case 4:
          break;

        default:
          cout << "Invalid choice\n";
          break;
        }
      } while (choice != 4);
      break;

    case 3:
      do
      {
        cout << "\n*** Worker Management System *** \n"
             << "1. Animal Caretaker\n"
             << "2. Field Worker\n"
             << "3. Back\n"
             << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
          cout << "\nAnimal Caretaker Here...\n"
               << "1. Produce product\n"
               << "2. Feed animal\n"
               << "3. Check Animal Health \n"
               << "\nEnter your choice: ";
          cin >> choice;

          if (choice == 1)
          {
            if (animalManager.checkAnimalValidity(animalCount))
              break;
            animalManager.displayAnimalList(animalCount, animals);
            int index = animalManager.getValidAnimalIndex(animalCount);
            if (index != -1)
              animals[index]->produce();
            break;
          }
          else if (choice == 2)
          {
            if (animalManager.checkAnimalValidity(animalCount))
              break;
            animalManager.displayAnimalList(animalCount, animals);
            int index = animalManager.getValidAnimalIndex(animalCount);
            if (index != -1)
              animals[index]->feed();
            break;
          }
          else if (choice == 3)
          {
            if (animalManager.checkAnimalValidity(animalCount))
              break;
            for (int i = 0; i < animalCount; i++)
            {
              animals[i]->checkHealth();
            }
            break;
          }
          else
          {
            cout << "Invalid choice.\n";
          }
          break;

        case 2:
          cout << "\nField Worker Here...\n"
               << "1. Water Crops\n"
               << "2. Harvest Crops\n"
               << "3. Check Crop Status\n"
               << "\nEnter your choice: ";
          cin >> choice;
          if (choice == 1)
          {
            if (!crop.getIsWatered())
            {
              wheat.water();
              corn.water();
            }
            else
              cout << "Crops are already watered\n";
          }
          else if (choice == 2)
          {
            harvestCrops(&wheat, wheatStock, "Wheat");
            harvestCrops(&corn, cornStock, "Corn");
          }
          else if (choice == 3)
          {
            wheat.checkStatus();
            corn.checkStatus();
          }
          else
            cout << "Invalid choice.\n";
          break;

        case 3:
          break;

        default:
          cout << "Invalid choice.\n";
          break;
        }
      } while (choice != 3);
      break;

    case 4:
      stimulateNewDay(animalCount, animals, &wheat, &corn);
      break;

    case 5:

      showAvailableStock(Cow::getMilkCapacity(), Chicken::getTotalEggs(), wheatStock, cornStock);
      break;

    case 6:
    {
      int index = 0, quantity = 0;
      int choice;

      cout << "\nWelcome to THE MARKET... \n"
           << "Current Balance: $" << balance << "\n"
           << "\n1. Buy goods"
           << "\n2. Sell goods"
           << "\n3. Back"
           << "\nEnter your choice: ";
      cin >> choice;

      if (choice == 3)
        break;

      int randomCornStock = getStock(), randomWheatStock = getStock(), randomMilkStock = getStock(), randomEggStock = getStock();
      double cornRandomUnit = getUnit(), wheatRandomUnit = getUnit(), milkRandomUnit = getUnit(), eggRandomUnit = getUnit();

      if (choice == 1)
      {
        if (balance <= 0)
        {
          cout << "\nInsufficient balance to make any purchases.\n";
          break;
        }
        cout << "\nStocks may vary with conditions\n";
        cout << "\nAvailable Stocks\n";
        cout << "1. Corn stock:  " << randomCornStock << " / per 2 units $" << cornRandomUnit;
        cout << "\n2. Wheat stock: " << randomWheatStock << " / per 2 units $" << wheatRandomUnit;
        cout << "\n3. Milk stock:  " << randomMilkStock << " / per 2 liters $" << milkRandomUnit;
        cout << "\n4. Eggs stock:  " << randomEggStock << " / per 2 units $" << eggRandomUnit << endl;

        cout << "\nEnter stock index and quantity to buy or (0) to leave The Market: ";
        cin >> index;
        if (index == 0)
          break;
        cin >> quantity;

        if (index <= 0 || index > 4 || quantity <= 0)
        {
          cout << "Invalid choice.\n";
          break;
        }
        if (index == 1)
        {
          if (checkQuantity(quantity, randomCornStock))
            break;
          double value = getValue(quantity, cornRandomUnit);
          buyStock(balance, cornStock, quantity, value);
        }
        else if (index == 2)
        {
          if (checkQuantity(quantity, randomWheatStock))
            break;
          double value = getValue(quantity, wheatRandomUnit);
          buyStock(balance, wheatStock, quantity, value);
        }
        else if (index == 3)
        {
          if (checkQuantity(quantity, randomMilkStock))
            break;
          double value = getValue(quantity, milkRandomUnit);
          buyStock(balance, stock, quantity, value);
          Cow::addMilk(quantity);
        }
        else if (index == 4)
        {
          if (checkQuantity(quantity, randomEggStock))
            break;
          double value = getValue(quantity, eggRandomUnit);
          buyStock(balance, stock, quantity, value);
          Chicken::addEgg(quantity);
        }
      }
      else if (choice == 2)
      {
        showAvailableStock(Cow::getMilkCapacity(), Chicken::getTotalEggs(), wheatStock, cornStock);
        cout << "\nEnter stock index and quantity to sell or (0) to leave The Market: ";
        cin >> index;
        if (index == 0)
          break;
        cin >> quantity;

        if (index <= 0 || index > 4 || quantity <= 0)
        {
          cout << "Invalid choice.\n";
          break;
        }

        if (index == 1)
        {
          if (checkQuantity(quantity, cornStock))
            break;
          double value = getValue(quantity, cornRandomUnit);
          sellStock(balance, cornStock, quantity, value);
        }
        else if (index == 2)
        {
          if (checkQuantity(quantity, Chicken::getTotalEggs()))
            break;
          double value = getValue(quantity, eggRandomUnit);
          sellStock(balance, stock, quantity, value);
          Chicken::removeEgg(quantity);
        }
        else if (index == 3)
        {

          if (checkQuantity(quantity, Cow::getMilkCapacity()))
            break;
          double value = getValue(quantity, milkRandomUnit);
          sellStock(balance, stock, quantity, value);
          Cow::removeMilk(quantity);
        }
        else if (index == 4)
        {
          if (checkQuantity(quantity, wheatStock))
            break;
          double value = getValue(quantity, wheatRandomUnit);
          sellStock(balance, wheatStock, quantity, value);
        }
      }
    }
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
