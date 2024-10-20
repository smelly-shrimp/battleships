#ifndef SHOOTING_H
#define SHOOTING_H

#include <string>
#include "screen.h"

class Shooting : public Screen
{
    public:
        void print() override;
        void selectShot();
    private:
        void _selectShotPos();
        void _askAgain(std::string msg);
};

#endif // !SHOOTING_H
