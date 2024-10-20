#ifndef ARRANGE_H
#define ARRANGE_H

#include <string>
#include <regex>
#include "screen.h"

class Arrange : public Screen
{
    public:
        void print() override;
        void selectShip();
    private:
        int _len;
        void _selectShipPos();
        int _setOrient(std::smatch matches);
        // void _createShip(int col, int row, int orient);
        void _askAgain(std::string msg);
};

#endif // !ARRANGE_H
