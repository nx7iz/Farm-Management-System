#include <iostream>

using namespace std;

void incrementPrice(double& price) {
  price *= 1.2;
}

int main() {
  double price = 100;

  incrementPrice(price);

  cout << price;
}