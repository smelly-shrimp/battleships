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
        int _x;
        int _y;
        void _printList();
        void _askAgain();
        // bool isNum(string st);
};

#endif // !ARRANGE_H
