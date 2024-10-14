#include <iostream>
#include "game.h"
#include "intro.h"
#include "welcome.h"
#include "tools.h"
#include "player.h"

void Game::setGameState(GameStates state)
{
    _state = state;

    Intro intro;
    Welcome welcome;

    Tools::clearConsole();
    
    switch(Game::getGameState()) {
        case INTRO:
            intro.print();
            break;
        case WELCOME:
            welcome.print();
            welcome.enemyIn();
            setGameState(GameStates::ARRANGE);
            break;
        case ARRANGE:
            cout << "Foo" << endl;
            break;
        default:
            std::cout << "PANIC! STOPPING EXECUTION! ILLEGAL STATE!" << std::endl;
            std::exit(0);
    }
}

GameStates Game::getGameState()
{
    return _state;
}
