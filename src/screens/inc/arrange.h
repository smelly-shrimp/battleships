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

struct ShipPos
{
    int row;
    int col;
    int orient;
};

class Arrange : public Screen
{
    public:
        Arrange();
        void print() override;
        Mode selectArrangeMode();
        void selectShip(Mode mode);
    private:
        ShipPos _selectShipPos(int len);
        ShipPos _autoSelectShipPos(int len);
        void _createShip(ShipPos& pos, int len);
};

#endif // !ARRANGE_H
