#ifndef SCREEN_H
#define SCREEN_H

#include "console.h"

class Screen
{
    public:
        virtual void print() = 0;
        virtual void update() = 0;
        virtual ~Screen() = default;
    protected:
        Console _console;
};

#endif // !SCREEN_H
