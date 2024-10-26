#ifndef SHOOTING_H
#define SHOOTING_H

#include <string>
#include "screen.h"

class Shooting : public Screen
{
    public:
        void print() override;
        int selectShot();
    private:
        void _selectShotPos();
        void _autoSelectShotPos();
        void _hit(int row, int col, int val, std::string rowName, std::string colName);
        void _askAgain(std::string msg);
};

#endif // !SHOOTING_H
