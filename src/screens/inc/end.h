#ifndef END_H
#define END_H

#include "screen.h"

class End : public Screen
{
    public:
        void print() override;
        void update() override;
        bool isPlayAgain();
        void saveScores();
};

#endif // !END_H
