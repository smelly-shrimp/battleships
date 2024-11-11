#ifndef END_H
#define END_H

#include "screen.h"

class End : public Screen
{
    public:
        void print() override;
        void update() override;
        bool isPlayAgain();
    private:
        void _printScores();
};

#endif // !END_H
