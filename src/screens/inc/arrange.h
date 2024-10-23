#ifndef ARRANGE_H
#define ARRANGE_H

#include <string>
#include <regex>
#include "screen.h"

enum class Mode
{
    MANUAL,
    AUTO
};

class Arrange : public Screen
{
    public:
        Arrange();
        Mode selectArrangeMode();
        void print() override;
        void selectShip(Mode arrangeMode);
    private:
        int _len;
        void _selectShipPos();
        void _autoSelectShipPos();
        int _setOrient(std::smatch matches);
        void _createShip(int row, int col, int orient);
        void _askAgain(std::string msg);
};

#endif // !ARRANGE_H
