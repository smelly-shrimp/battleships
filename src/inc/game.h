#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "screen.h"

enum GameStates
{
    UNDEFINED,
    INTRO,
    WELCOME,
    ARRANGE,
    SHOOTING,
    END,
};

class Game
{
    public:
        Game();
        inline static Player* p1;
        inline static Player* p2;
        static GameStates getGameState();
        static void setCurrPlayer(Player* p);
        static void setCurrEnemy(Player* p);
        static Player* getCurrPlayer();
        static Player* getCurrEnemy();
        static void changePlayers();
    private:
        static void _play();
        inline static GameStates _state;
        inline static Player* _currPlayer;
        inline static Player* _currEnemy;
        inline static int arrangeMode{};
        inline static void setScreen(Screen* screen);
        inline static Screen* _screen{};
};

#endif // !GAME_H
