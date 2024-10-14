#ifndef WELCOME_H
#define WELCOME_H

#include "screen.h"
#include "player.h"

class Welcome : public Screen
{
    public:
        void print() override;
        Player* inputEnemy();
};

#endif // !WELCOME_H
