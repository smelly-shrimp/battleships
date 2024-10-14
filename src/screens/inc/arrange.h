#ifndef ARRANGE_H
#define ARRANGE_H

#include <iostream>
#include "screen.h"

class Arrange : public Screen
{
    public:
        void print() override;
        void shipsIn();
    private:
        void _printList();
        void _askForShips(std::string ans);
};

#endif // !ARRANGE_H
