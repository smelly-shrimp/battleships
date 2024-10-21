#ifndef ARRANGE_H
#define ARRANGE_H

#include <string>
#include <regex>
#include "screen.h"

class Arrange : public Screen
{
    public:
        Arrange();
        int selectArrangeMode();
        void print() override;
        void selectShip(int arrangeMode);
    private:
        int _len;
        void _selectShipPos();
        void _autoSelectShipPos();
        int _setOrient(std::smatch matches);
        void _askAgain(std::string msg);
};

#endif // !ARRANGE_H
