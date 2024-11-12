#ifndef SHOOTING_H
#define SHOOTING_H

#include <string>
#include "screen.h"
#include "ship.h"

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
    int firstRow;
    int firstCol;
    int prevRow;
    int prevCol;

    int hitCount;
    int hitStage;
};

class Shooting : public Screen
{
    public:
        void print() override;
        void update() override;
    private:
        ShotInfo _humanShotInfo{};
        ShotInfo _compShotInfo{};
        ShotInfo* _currShotInfo{};
        bool _isEnd();
        Reactions _checkReaction();
        void _selectShotPos();
        void _autoSelectShotPos();
        bool _shoot();
        int _getMaxChunk();
        void _inform(std::string msg, InfoType type);
};

#endif // !SHOOTING_H
