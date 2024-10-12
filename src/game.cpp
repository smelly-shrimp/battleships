#include <iostream>
#include "game.h"
#include "intro.h"
#include "welcome.h"
#include "tools.h"

void Game::setGameState(GameStates state)
{
    _state = state;

    Intro intro;
    Welcome welcome;

    Tools::clearConsole();
    
    switch(Game::getGameState()) {
        case GameStates::INTRO:
            intro.print();
            break;
        case GameStates::WELCOME:
            welcome.print();
            break;
        default:
    }
}

GameStates Game::getGameState()
{
    return _state;
}
