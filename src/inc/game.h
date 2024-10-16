#ifndef GAME_H
#define GAME_H

#include "player.h"

enum GameStates
{
    UNDEFINED,
    INTRO,
    WELCOME,
    ARRANGE,
};

class Game
{
    public:
        inline static Player* p1;
        inline static Player* p2;
        static void setGameState(GameStates state);
        static GameStates getGameState();
    private:
        inline static GameStates _state;
        // static Player* getCurrPlayer();
        // inline static Player* _pcurr;
};

#endif // !GAME_H
