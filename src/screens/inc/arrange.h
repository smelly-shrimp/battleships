#ifndef ARRANGE_H
#define ARRANGE_H

#include <string>
#include <regex>
#include "screen.h"

class Arrange : public Screen
{
    public:
        void print() override;
        void inputShip();
    private:
        int _len;
        void _inputShipPos();
        int _setOrient(std::smatch matches);
        void _createShip(int x, int y, int orient);
        void _askAgain(std::string msg);
};

#endif // !ARRANGE_H
