#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

using namespace std;

class Console
{
    public:
        string input();
        bool isAnswer(string arg, string valid);
};

#endif // !CONSOLE_H
