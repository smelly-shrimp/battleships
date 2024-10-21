#ifndef WELCOME_H
#define WELCOME_H

#include <string>
#include "screen.h"
#include "player.h"

class Welcome : public Screen
{
    public:
        void print() override;
        Player* selectEnemy();
    private:
        void _askAgain(std::string msg);
};

#endif // !WELCOME_H
