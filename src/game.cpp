#include "game.h"
#include "intro.h"

void Game::setGameState(GameStates state)
{
    _state = state;

    Intro intro;

    switch(Game::getGameState()) {
        case GameStates::INTRO:
            intro.print();
            break;
        case GameStates::WELCOME:
            break;
        default:
    }
}

GameStates Game::getGameState()
{
    return _state;
}
