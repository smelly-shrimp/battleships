#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

using namespace std;

class Console
{
    private:
        void _drawChars(int length, string color);
    public:
        void drawLine(string color = "", bool isError = false);
        string input(string msg);
        bool isAnswer(string arg, string valid);
};

#endif // !CONSOLE_H
