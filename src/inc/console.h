#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

enum class InfoType
{
    DEF,
    SUCC,
    WARN,
    ERR,
    IN,
};

struct InfoData
{
    std::string msg;
    std::string color;
};

class Console
{
    public:
        std::string input(std::string msg);
        bool isAnswer(std::string arg, std::string valid);
        void drawInfo(std::string msg, InfoType type);
        void drawHeader(std::string msg);
        void drawShipList(bool isArrange, bool isComp);
        void drawGrid(bool isArrange, bool isComp);
        void cover();
        void center(std::string msg);
    private:
        void _drawBar(std::string msg, InfoType type, bool isHeader);
        InfoData _getInfoData(InfoType type);
};

#endif // !CONSOLE_H
