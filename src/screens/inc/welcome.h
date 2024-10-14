#ifndef WELCOME_H
#define WELCOME_H

#include "screen.h"

class Welcome : public Screen
{
    public:
        void print() override;
        void enemyIn();
    private:
        void _validate(string ans);
};

#endif // !WELCOME_H
