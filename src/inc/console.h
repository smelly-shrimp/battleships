#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

class Console
{
    public:
        std::string input(std::string msg, std::string name = "CAPTAIN HOOK");
        bool isAnswer(std::string arg, std::string valid);
        void drawInfo(std::string msg);
        void drawError(std::string msg);
    private:
        void _drawChars(int length, std::string color);
        void _drawLine(std::string color = "", bool isError = false);
};

#endif // !CONSOLE_H
