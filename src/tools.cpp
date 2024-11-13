#include <chrono>
#include <format>
#include <string>
#include <thread>

#include "tools.h"

using std::string;

void Tools::waitMs(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Tools::clearConsole()
{
    #if __linux__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
        printf("\033[2J");
    #endif
}

string Tools::lower(string st)
{
    string r;
    for (char s : st) r.push_back(tolower(s));
    return r;
}

std::string Tools::insertChars(string c, int t)
{
    string s;
    for (int i = 0; i < t; i++) s.append(c);
    return s;
}
