#ifndef END_H
#define END_H

#include "screen.h"

class End : public Screen
{
    public:
        void print() override;
        bool isPlayAgain();
        void saveScores();
};

#endif // !END_H
