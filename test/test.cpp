#include <iostream>
#include <cstdlib>
#include <ctime>

// Color definitions (add this)
#ifdef _WIN32
#include <windows.h>
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

using namespace std;

int main() {
  #ifdef _WIN32
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING);
  cout << COLOR_RED << "This should be red!" << COLOR_RESET << endl;
  cout << COLOR_GREEN << "This should be green!" << COLOR_RESET << endl;
  #endif
}