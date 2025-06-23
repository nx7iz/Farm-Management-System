#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Cab
{
protected:
  float fuel;
  float balance;
  int totalRides;
  int successfulRides;
  int declinedRides;
  float distanceTravelled;

public:
  Cab()
  {
    fuel = 25.0;
    balance = 0.0;
    totalRides = successfulRides = declinedRides = 0;
    distanceTravelled = 0.0;
  }

  virtual void startRide(int distance)
  {
    float fare = distance * 0.6;
  float fuelNeeded = distance * 0.5;
  
  totalRides++;
  
  if (fuel >= fuelNeeded) {
    fuel -= fuelNeeded;
    balance += fare;
    successfulRides++;
    distanceTravelled += distance;
    cout << "Economy ride completed for " << distance << " km. Fare: $" << fare << endl;
  } else {
    declinedRides++;
    cout << "Economy ride declined due to low fuel. \n";
  }
  }

  void refillFuel(float liters)
  {
    float cost = liters * 1.2;
    if (fuel + liters >= 25)
    {
      cout << "Tank full. Cannot refil more than 25L. \n";
    }
    else if (balance >= cost)
    {
      fuel += liters;
      balance -= cost;
      cout << "Refilled " << liters << " L. Cost: $" << cost << "\n";
    }
    else
    {
      cout << "Not enough balance to refill. \n";
    }
  }

  void showStatus() {
    cout << "\nCab Report:" << endl;
    cout << "Total Rides: " << totalRides << endl;
    cout << "Successful: " << successfulRides << endl;
    cout << "Declined: " << declinedRides << endl;
    cout << "Balance: $" << balance << endl;
    cout << "Fuel: " << fuel << "L" << endl;
    cout << "Distance Travelled: " << distanceTravelled << " km\n";
  }
};

class PremiumCab: public Cab {
public:
  void startRide(int distance) override {
    float fare = distance * 1.2;
    float fuelNeeded = distance * 0.6;

    totalRides++;

    if (fuel >= fuelNeeded) {
      fuel -= fuelNeeded;
      balance += fare;
      successfulRides++;
      distanceTravelled += distance;
      cout << "Premium ride completed for " << distance << " km. Fare: $" << fare << endl;
    } else {
      declinedRides++;
      cout << "Premium ride declined due to low fuel. \n";
    }
  }
};

// void Cab::startRide(int distance)  {
  
// }

int main() {
  srand(time(0));

  Cab ecoCab;
  PremiumCab premCab;

  const int totalPassengers = 5;

  for (int i = 0; i < totalPassengers; i++) {
    cout << "\n --- Passenger " << i + 1 << " --- \n";
    int distance = rand() % 21 + 5;
    int cabType = rand() % 2;

    if (cabType == 0) {
      cout << "Requesting Economy Cab for " << distance << " km/h\n";
      ecoCab.startRide(distance);
    } else {
      cout << "Requesting Premium Cab for " << distance << " km/h\n";
      premCab.startRide(distance);
    }

    if (rand() % 3 == 0) {
      float refillAmount = rand() % 5 + 1;
      cout << "Random refuel: " << refillAmount << " L\n";
      if (cabType == 0) {
        ecoCab.refillFuel(refillAmount);
      } else {
        premCab.refillFuel(refillAmount);
      }
    }

  }

  cout << "\n--- FINAL CAB STATUS ---\n";
    cout << "\n[ECONOMY CAB]";
    ecoCab.showStatus();

    cout << "\n[PREMIUM CAB]";
    premCab.showStatus();
}

