#ifndef TOOLS_H
#define TOOLS_H

#include <map>
#include <string>
using namespace std;

class Tools
{
    public:
        static void clearConsole();
        static void waitMs(int ms);
        static string lower(string st);
        inline static map<string, string> colors = { { "red", "\x1B[31m" }, { "endf", "\033[0m" } };
};

#endif // !TOOLS_H
