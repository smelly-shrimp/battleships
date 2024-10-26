#ifndef SHOOTING_H
#define SHOOTING_H

#include <string>
#include "screen.h"
#include "ship.h"

enum class SquareValues
{
    MISS = 2,
    HIT = 3,
    SUNK = 4,
};

enum class Reactions
{
    HIT,
    AGAIN,
    MISS,
};

class Shooting : public Screen
{
    public:
        Shooting();
        void print() override;
        int selectShot();
    private:
        Reactions checkReaction(int row, int col);
        void _selectShotPos();
        void _autoSelectShotPos(bool isHit = false);
        void _hitShip(int row, int col);
        void _sunkShip(Ship* ship);
        void _askAgain(std::string msg);
};

#endif // !SHOOTING_H
