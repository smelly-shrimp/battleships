#ifndef ARRANGE_H
#define ARRANGE_H

#include <string>
#include <regex>
#include "screen.h"

enum class Mode
{
    MANUAL,
    AUTO,
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
        void print() override;
        void update() override;
        Mode selectArrangeMode();
    private:
        void _selectShip(Mode mode);
        ShipPos _selectShipPos(int len);
        ShipPos _autoSelectShipPos(int len);
        void _createShip(ShipPos& pos, int len);
};

#endif // !ARRANGE_H
