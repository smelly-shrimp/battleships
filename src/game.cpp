#include <iostream>
#include "game.h"
#include "intro.h"
#include "welcome.h"
#include "arrange.h"
#include "shooting.h"
#include "tools.h"
#include "player.h"

using namespace std;

Game::Game()
{
    _state = GameStates::INTRO;
    _play();
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

void Game::changePlayers()
{
    Player* player = Game::getCurrPlayer();
    Game::setCurrPlayer(Game::getCurrEnemy());
    Game::setCurrEnemy(player);
}

void Game::_play()
{
    Intro intro;
    Welcome welcome;
    Arrange arrange;
    Shooting shooting;

    while (true) {
        Tools::clearConsole();

        switch(_state) {
        case INTRO:
            intro.print();

            _state = GameStates::WELCOME;
            break;
        case WELCOME:
            welcome.print();
            p1 = new Human("PLAYER_1", PlayerTypes::HUMAN);
            p2 = welcome.selectEnemy();
            setCurrPlayer(p1);
            setCurrEnemy(p2);

            _state = GameStates::ARRANGE;
            break;
        case ARRANGE:
            for (int i = 0; i < 2; i++) {
                cout << getCurrPlayer()->getName();
                if (getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
                    arrangeMode = arrange.selectArrangeMode();
                    arrange.print();
                    arrange.selectShip(arrangeMode);
                }
                else arrange.selectShip(1);
            }
            break;
        case SHOOTING:
            shooting.print();
            shooting.selectShot();
            break;
        default:
            cout << Tools::colors["red"] << "PANIC! ILLEGAL STATE! STOPPING EXECUTION!" << Tools::colors["endf"] << endl;
            exit(0);
        }
    }
}
