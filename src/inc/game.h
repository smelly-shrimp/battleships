#ifndef GAME_H
#define GAME_H

#include "player.h"

enum GameStates
{
    UNDEFINED,
    INTRO,
    WELCOME,
    ARRANGE,
    SHOOTING,
};

class Game
{
    public:
        inline static Player* p1;
        inline static Player* p2;
        static void setGameState(GameStates state);
        static GameStates getGameState();
        static void setCurrPlayer(Player* p);
        static Player* getCurrPlayer();
    private:
        inline static GameStates _state;
        inline static Player* _currPlayer;
};

#endif // !GAME_H
