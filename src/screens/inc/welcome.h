#ifndef WELCOME_H
#define WELCOME_H

#include <string>
#include "screen.h"
#include "player.h"

class Welcome : public Screen
{
    public:
        void print() override;
        void update() override;
        Player* selectEnemy();
};

#endif // !WELCOME_H
