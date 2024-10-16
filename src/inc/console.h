#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

using namespace std;

class Console
{
    public:
        void drawLine(string color = "", bool isError = false);
        string input(string msg, string name = "CAPTAIN HOOK");
        bool isAnswer(string arg, string valid);
        void drawError(string msg);
    private:
        void _drawChars(int length, string color);
};

#endif // !CONSOLE_H
