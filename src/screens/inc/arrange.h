#ifndef ARRANGE_H
#define ARRANGE_H

#include <iostream>
#include "screen.h"

class Arrange : public Screen
{
    public:
        void print() override;
        void inputShip();
    private:
        int _x;
        int _y;
        int _rotation;
        void _askAgain();
        void _inputShipPos();
        void _inputShipRot(int length);
        void _createShip(int length);
};

#endif // !ARRANGE_H
