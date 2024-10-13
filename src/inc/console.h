#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

using namespace std;

class Console
{
    private:
    public:
        vector<string> validateArgv(string arg, int argc);
};

#endif // !CONSOLE_H
