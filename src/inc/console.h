#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

class Console
{
    public:
        std::string input(std::string msg);
        bool isAnswer(std::string arg, std::string valid);
        void drawInfo(std::string msg);
        void drawError(std::string msg);
        void drawHeader(std::string action, bool isTop = false);
    private:
        void _drawLine(std::string color = "", bool isError = false);
};

#endif // !CONSOLE_H
