#ifndef SHOOTING_H
#define SHOOTING_H

#include "screen.h"

class Shooting : public Screen
{
    public:
        void print() override;
        void inputShot();
};

#endif // !SHOOTING_H
