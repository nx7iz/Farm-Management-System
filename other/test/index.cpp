#include <iostream>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
using namespace std;

int main() {
    srand(time(0));  // seed random number generator

    double unitRandom = 0.5 + static_cast<double>(rand()) / RAND_MAX;  // range: 0.5 to 1.5
    cout << "Random value: " << unitRandom << endl;

    return 0;
}
