#include <string>
#include <chrono>
#include <thread>
#include "tools.h"

using namespace std;

void Tools::clearConsole()
{
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
