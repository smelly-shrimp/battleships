#ifndef TOOLS_H
#define TOOLS_H

#include <string>
using namespace std;

class Tools
{
    public:
        static void clearConsole();
        static void waitMs(int ms);
        static string lower(string st);
};

#endif // !TOOLS_H
