#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Color definitions
#ifdef _WIN32
#define COLOR_RED     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define COLOR_GREEN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define COLOR_YELLOW  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define COLOR_BLUE    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9)
#define COLOR_RESET   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#else
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_RESET   "\033[0m"
#endif

// Utility functions
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sleep(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void printHeader(const string& title) {
    clearScreen();
    cout << COLOR_GREEN << "==================================================\n";
    cout << "          " << title << "\n";
    cout << "==================================================\n" << COLOR_RESET;
    
    cout << COLOR_YELLOW
         << "       .-^-.\n"
         << "      / 0 0 \\ \n"
         << "     |   ∆   |   ___\n" 
         << "      \\  -  /  //   \\\\\n"
         << "       `~~~`  ((     ))\n"
         << "               \\\\___//\n"
         << COLOR_RESET;
}

void pressEnterToContinue() {
    cout << COLOR_BLUE << "\nPress Enter to continue..." << COLOR_RESET;
    // Clear any existing input
    cin.clear();
    // Ignore everything until newline
    while (cin.get() != '\n') {
        continue;
    }
}

class Menu {
public:
    static int showMenu(const string& title, const vector<string>& options) {
        printHeader(title);
        
        cout << COLOR_BLUE << " OPTIONS:\n" << COLOR_RESET;
        cout << COLOR_GREEN << "------------------------------------------\n" << COLOR_RESET;
        
        for (int i = 0; i < options.size(); i++) {
            cout << COLOR_YELLOW << " " << i+1 << ". " << COLOR_RESET << options[i] << "\n";
        }
        cout << COLOR_RED << " 0. Back\n" << COLOR_RESET;
        cout << COLOR_GREEN << "------------------------------------------\n" << COLOR_RESET;
        
        int choice;
        cout << "Enter your choice: ";
    while (true) {
      cin >> choice;
    
      if (cin.fail() || choice < 0 || choice > options.size()) {
        // Clear error state
        cin.clear();
        
        // Discard remaining input
        char ch;
        while (cin.get(ch) && ch != '\n') {
            continue;
        }
        
        cout << COLOR_RED << "Invalid input. Please enter a number between 0 and " 
             << options.size() << ": " << COLOR_RESET;
      } else {
        // Valid input received
        break;
      }
  }
        return choice;
    }
};

class Animal {
protected:
    string name;
    int health;
    bool fedToday;

public:
    Animal() : health(100), fedToday(false) {}
    Animal(string n) : name(n), health(100), fedToday(false) {}

    virtual void feed() = 0;
    virtual void newDay() = 0;
    virtual void checkHealth() = 0;
    virtual void produce() = 0;

    string getName() { return name; }
    int getHealth() { return health; }

    void displayStatus() {
        string healthColor;
        if (health > 70) healthColor = COLOR_GREEN;
        else if (health > 30) healthColor = COLOR_YELLOW;
        else healthColor = COLOR_RED;
        
        cout << COLOR_BLUE << " " << name << COLOR_RESET << " [";
        cout << healthColor << health << "/100" << COLOR_RESET << "]";
        cout << " - " << (fedToday ? COLOR_GREEN + "Fed" : COLOR_RED + "Hungry") << COLOR_RESET;
    }

    virtual ~Animal() {}
};

class Cow : public Animal {
    bool milkProduced;
    static int milkCapacity;

public:
    Cow() : milkProduced(false) {}
    Cow(string n) : Animal(n), milkProduced(false) {}

    void feed() override {
        fedToday = true;
        health = min(100, health + rand() % 12 + 4);
        cout << COLOR_GREEN << "\nFed cow " << name << " with hay.\n" << COLOR_RESET;
    }

    void newDay() override {
        if (!fedToday && health > 0) {
            health -= rand() % 9 + 7;
            cout << COLOR_RED << "\n" << name << " was not fed. Health decreased!\n" << COLOR_RESET;
        }
        fedToday = false;
        milkProduced = false;
        
        if (health <= 0) {
            health = 0;
            cout << COLOR_RED << name << " has died from starvation!\n" << COLOR_RESET;
        }
    }

    void produce() override {
        if (health > 55 && !milkProduced) {
            int random = rand() % 4 + 2;
            milkCapacity += random;
            cout << COLOR_YELLOW << "\nCow is producing milk...\n" << COLOR_RESET;
            cout << COLOR_GREEN << name << " produced " << random << " liters of milk.\n" << COLOR_RESET;
            milkProduced = true;
        }
        else if (health <= 55) {
            cout << COLOR_RED << "\nHealth too low. Cannot produce milk.\n" << COLOR_RESET;
        }
    }

    void checkHealth() override {
        if (health < 50) {
            cout << COLOR_RED << "\n" << name << " health CRITICAL: " << health << "/100\n" << COLOR_RESET;
        } else {
            cout << COLOR_GREEN << "\n" << name << " health: " << health << "/100\n" << COLOR_RESET;
        }
    }

    static int getMilkCapacity() { return milkCapacity; }
    static void addMilk(int qty) { milkCapacity += qty; }
    static void removeMilk(int qty) { milkCapacity = max(0, milkCapacity - qty); }
};

int Cow::milkCapacity = 0;

class Chicken : public Animal {
    static int totalEggs;
    bool eggsLaid;

public:
    Chicken() : eggsLaid(false) {}
    Chicken(string n) : Animal(n), eggsLaid(false) {}

    void feed() override {
        fedToday = true;
        health = min(100, health + rand() % 12 + 4);
        cout << COLOR_GREEN << "\nFed chicken " << name << " with grains.\n" << COLOR_RESET;
    }

    void newDay() override {
        if (!fedToday && health > 0) {
            health -= rand() % 9 + 7;
            cout << COLOR_RED << "\n" << name << " was not fed. Health decreased!\n" << COLOR_RESET;
        }
        fedToday = false;
        eggsLaid = false;
        
        if (health <= 0) {
            health = 0;
            cout << COLOR_RED << name << " has died from starvation!\n" << COLOR_RESET;
        }
    }

    void produce() override {
        if (health > 55 && !eggsLaid) {
            int random = rand() % 5 + 1;
            totalEggs += random;
            cout << COLOR_YELLOW << "\nChicken is laying eggs...\n" << COLOR_RESET;
            cout << COLOR_GREEN << name << " laid " << random << " eggs.\n" << COLOR_RESET;
            eggsLaid = true;
        }
        else if (health <= 55) {
            cout << COLOR_RED << "\nHealth too low. Cannot lay eggs.\n" << COLOR_RESET;
        }
    }

    void checkHealth() override {
        if (health < 50) {
            cout << COLOR_RED << "\n" << name << " health CRITICAL: " << health << "/100\n" << COLOR_RESET;
        } else {
            cout << COLOR_GREEN << "\n" << name << " health: " << health << "/100\n" << COLOR_RESET;
        }
    }

    static int getTotalEggs() { return totalEggs; }
    static void addEgg(int qty) { totalEggs += qty; }
    static void removeEgg(int qty) { totalEggs = max(0, totalEggs - qty); }
};

int Chicken::totalEggs = 0;

// [Rest of your classes (Crop, Worker, etc.) would follow the same pattern...]

int main() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif

    srand(time(0));

    // Initialize your game state here
    const int maxAnimals = 10;
    Animal* animals[maxAnimals];
    int animalCount = 0;
    
    while (true) {
        vector<string> mainMenu = {
            "Animal Management",
            "Crop Management",
            "Worker Management",
            "Start New Day",
            "Check Stock Levels",
            "Visit Market"
        };
        
        int choice = Menu::showMenu("DIGITAL FARM MANAGEMENT SYSTEM", mainMenu);
        
        switch (choice) {
            case 1: {
                vector<string> animalMenu = {
                    "Add Animal",
                    "View Animals",
                    "Remove Animal",
                    "Feed Animals"
                };
                int animalChoice = Menu::showMenu("ANIMAL MANAGEMENT", animalMenu);
                // Handle animal management...
                break;
            }
            // Other cases...
            case 0: return 0;
        }
    }

    // Cleanup
    for (int i = 0; i < animalCount; i++) {
        delete animals[i];
    }
    return 0;
}