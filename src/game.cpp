#include <iostream>
#include "game.h"
#include "intro.h"
#include "welcome.h"
#include "arrange.h"
#include "tools.h"
#include "player.h"

using namespace std;

void Game::setGameState(GameStates state)
{
    _state = state;

    Intro intro;
    Welcome welcome;
    Arrange arrange;

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
            arrange.print();
            arrange.shipsIn();
            break;
        default:
            cout << "PANIC! ILLEGAL STATE! STOPPING EXECUTION!" << endl;
            exit(0);
    }
}

GameStates Game::getGameState()
{
    return _state;
}
