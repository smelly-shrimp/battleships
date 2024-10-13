#ifndef GAME_H
#define GAME_H

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
        static void setGameState(GameStates state);
        static GameStates getGameState();
};

#endif // !GAME_H
