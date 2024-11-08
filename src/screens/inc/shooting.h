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
    SUNK,
    AGAIN,
    MISS,
};

struct ShotPos
{
    int row;
    int col;
};

class Shooting : public Screen
{
    public:
        Shooting();
        void print() override;
        int selectShot();
    private:
        int _stage{};
        void _selectShotPos();
        void _autoSelectShotPos(bool isHit, ShotPos hitPos = {0, 0});
        Reactions checkReaction(ShotPos& pos);
        int _getMaxChunk();
};

#endif // !SHOOTING_H
