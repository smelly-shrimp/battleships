#include <iostream>
#include "game.h"
#include "intro.h"
#include "welcome.h"
#include "arrange.h"
#include "shooting.h"
#include "tools.h"
#include "player.h"

using namespace std;

void Game::setGameState(GameStates state)
{
    _state = state;

    Intro intro;
    Welcome welcome;
    Arrange arrange;
    Shooting shooting;

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
            setCurrEnemy(p2);
            setGameState(GameStates::SHOOTING);
            break;
        case ARRANGE:
            arrange.print();
            arrange.inputShip();
            break;
        case SHOOTING:
            shooting.print();
            shooting.inputShot();
            // Game::setGameState(GameStates::SHOOTING);
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

void Game::setCurrEnemy(Player *p)
{
    _currEnemy = p;
}

Player *Game::getCurrPlayer()
{
    return _currPlayer;
}

Player *Game::getCurrEnemy()
{
    return _currEnemy;
}
