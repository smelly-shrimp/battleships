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
    private:
        inline static GameStates _state;
    public:
        inline static Player* p1;
        inline static Player* p2;
        static void setGameState(GameStates state);
        static GameStates getGameState();
};

#endif // !GAME_H
