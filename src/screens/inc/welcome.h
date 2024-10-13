#ifndef WELCOME_H
#define WELCOME_H

#include "screen.h"

class Welcome : public Screen
{
    private:
        void _validate(string ans);
    public:
        void print() override;
        void enemyIn();
};

#endif // !WELCOME_H
