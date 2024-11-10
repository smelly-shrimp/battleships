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

struct ShotInfo
{
    int row;
    int col;
    int prevRow;
    int prevCol;
    int hitCount;
    int hitStage;
    int dir;
};

class Shooting : public Screen
{
    public:
        void print() override;
        void update() override;
    private:
        ShotInfo _shotInfo{};
        bool _isEnd();
        Reactions _checkReaction();
        void _selectShotPos();
        void _autoSelectShotPos();
        bool _shoot();
        int _getMaxChunk();
        void _inform(std::string msg, InfoType type);
};

#endif // !SHOOTING_H
