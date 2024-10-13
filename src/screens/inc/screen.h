#ifndef SCREEN_H
#define SCREEN_H

#include "console.h"

class Screen
{
    private:
    public:
        Console console;
        virtual void print() = 0;
};

#endif // !SCREEN_H
