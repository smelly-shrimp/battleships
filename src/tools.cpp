#include <string>
#include <format>
#include <chrono>
#include <thread>
#include "tools.h"

using namespace std;

void Tools::clearConsole()
{
    // #if __linux__
    //     system("clear");
    // #elif __APPLE__
    //     system("clear");
    // #elif _WIN32
    //     system("cls");
    // #else
    //     printf("\033[2J");
    // #endif

    printf("\033[2J");
}

void Tools::waitMs(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

string Tools::lower(string st)
{
    string r;
    for (char s : st) {
        r += tolower(s);
    }

    return r;
}

std::string Tools::insertChars(string c, int t)
{
    string s;
    for (int i = 0; i < t; i++) {
        s = format("{}{}", s, c);
    }
    return s;
}
