#include <iostream>

using namespace std;

class Crop
{
protected:
  string name;
  int daysToHarvest;
  bool isWatered;

public:
  Crop(string n = "") : name(n), isWatered(false) {}

  virtual void grow()
  {
    cout << "Seed of " << name << " has been planted. Will grow soon.\n";
  }

  virtual void newDay()
  {
    if (daysToHarvest != -1)
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
      isWatered = false;
    }
  }
  virtual void water()
  {
    if (daysToHarvest != -1)
      isWatered = true;
  }

  virtual int harvestYield()
  {
    return rand() % 11 + 10;
  }

  void setDaysToHarvest(int days) { daysToHarvest = days; }
  void setDaysLeft(int days) { daysToHarvest -= days; }
  int getDaysToHarvest() { return daysToHarvest; }

  virtual void checkStatus()
  {
    cout << name << ": " << (daysToHarvest > 0 ? "Growing" : "Ready to harvest") << "(" << daysToHarvest << " days remaining)\n";
  }

  bool getIsWatered() { return isWatered; }
};

class Wheat : public Crop {

};

class Corn : public Crop {

};

void harvestCrops(Crop crop, int &stock, string name)
{
  if (crop.getDaysToHarvest() == 0)
  {
    int yield = crop.harvestYield();
    stock += yield;
    cout << name << " harvested! Yield: " << yield << " units.\n";
    crop.setDaysToHarvest(-1);
  }
  else
  {
    if (crop.getDaysToHarvest() != -1)
    {
      cout << name << " not ready or planted. Days left to harvest: " << crop.getDaysToHarvest() << "\n";
    }
    else
    {
      cout << name << " not ready or planted.\n";
    }
  }
}

int main()
{

  Wheat wheat;
  Corn corn;

  int wheatStock = 0;
  int cornStock = 0;
  int choice;
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
    wheat.getDaysToHarvest();
    break;

  case 2:
    corn.grow();
    corn.getDaysToHarvest();
    break;

  case 3:
    harvestCrops(wheat, wheatStock, "Wheat");
    harvestCrops(corn, cornStock, "Corn");

    break;
  }
}