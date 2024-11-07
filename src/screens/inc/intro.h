#ifndef INTRO_H
#define INTRO_H

#include "screen.h"

class Intro : public Screen
{
    public:
        void print() override;
        void update() override;
};

#endif // !INTRO_H
