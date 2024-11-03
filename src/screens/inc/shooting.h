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
        void selectShot();
        bool isEnd();
    private:
        int _stage{};
        bool _isHit{};
        ShotPos _hitPos{};
        void _selectShotPos();
        void _autoSelectShotPos();
        Reactions _checkReaction(ShotPos& pos);
        int _getMaxChunk();
};

#endif // !SHOOTING_H
