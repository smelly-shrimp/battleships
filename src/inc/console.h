#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

using namespace std;

class Console
{
    private:
        vector<string> _validateArgv(string arg, string valid);
    public:
        void inputArgv(string arg, string valid);
};

#endif // !CONSOLE_H
