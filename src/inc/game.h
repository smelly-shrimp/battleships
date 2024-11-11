#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "screen.h"

enum class GameStates
{
    INTRO,
    WELCOME,
    ARRANGE,
    SHOOTING,
    END,
};

enum class SquareValues
{
    OCCUP = -1,
    MISS = 2,
    HIT = 3,
    SUNK = 4,
};

class Game
{
    public:
        Game();
        static void setCurrPlayer(Player* p);
        static void setCurrEnemy(Player* p);
        static Player* getCurrPlayer();
        static Player* getCurrEnemy();
        static bool isHvsH();
        static void changePlayers();
    private:
        inline static GameStates _state{};
        inline static Player* _currPlayer{};
        inline static Player* _currEnemy{};
        inline static int arrangeMode{};
        inline static Screen* _screen{};
        static void _play();
        static void _setScreen(Screen* screen);
};

#endif // !GAME_H
