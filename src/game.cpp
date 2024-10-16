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
            p1 = new Human("PLAYER_1");
            p2 = welcome.inputEnemy();
            setCurrPlayer(p1);
            setGameState(GameStates::ARRANGE);
            break;
        case ARRANGE:
            arrange.print();
            arrange.inputShips();
            break;
        default:
            cout << Tools::colors["red"] << "PANIC! ILLEGAL STATE! STOPPING EXECUTION!" << Tools::colors["endf"] << endl;
            exit(0);
    }
}

GameStates Game::getGameState()
{
    return _state;
}

void Game::setCurrPlayer(Player* p)
{
    _currPlayer = p;
}

Player *Game::getCurrPlayer()
{
    return _currPlayer;
}
