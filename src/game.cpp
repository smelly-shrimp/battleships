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
    _state = GameStates::WELCOME;
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
            p1 = new Human("PLAYER_1", PlayerTypes::HUMAN);
            setCurrPlayer(p1);

            welcome.print();
            p2 = welcome.selectEnemy();
            setCurrEnemy(p2);

            _state = GameStates::ARRANGE;
            break;
        case ARRANGE:
            for (int i = 0; i < 2; i++) {
                if (getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
                    arrange.selectShip(arrange.selectArrangeMode());
                    // arrangeMode = arrange.selectArrangeMode();
                    // arrange.print();
                    // arrange.selectShip(arrangeMode);
                }
                else arrange.selectShip(1);
                
            }

            _state = GameStates::SHOOTING;
            break;
        case SHOOTING:
            while (true) {
                shooting.print();
                shooting.selectShot();
                changePlayers();
            }
            exit(0);
            break;
        default:
            cout << Tools::ft["red"] << "PANIC! ILLEGAL STATE! STOPPING EXECUTION!" << Tools::ft["endf"] << endl;
            exit(0);
        }
    }
}
