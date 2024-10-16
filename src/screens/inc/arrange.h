#ifndef ARRANGE_H
#define ARRANGE_H

#include <iostream>
#include "screen.h"

class Arrange : public Screen
{
    public:
        void print() override;
        void inputShips();
    private:
        void _printList();
};

#endif // !ARRANGE_H
