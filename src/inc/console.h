#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

class Console
{
    public:
        void drawLine(std::string color = "", bool isError = false);
        std::string input(std::string msg, std::string name = "CAPTAIN HOOK");
        bool isAnswer(std::string arg, std::string valid);
        void drawError(std::string msg);
    private:
        void _drawChars(int length, std::string color);
};

#endif // !CONSOLE_H
