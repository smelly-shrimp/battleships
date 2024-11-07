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
        // Shooting();
        void print() override;
        void update() override;
        // void selectShot();
        bool isEnd();
    private:
        int _stage{};
        bool _isHit{};
        ShotPos _hitPos{};
        Reactions _checkReaction(ShotPos pos);
        ShotPos _selectShotPos();
        ShotPos _autoSelectShotPos();
        void _shoot(ShotPos pos);
        int _getMaxChunk();
        void _inform(ShotPos pos, std::string msg, InfoType type);
};

#endif // !SHOOTING_H
