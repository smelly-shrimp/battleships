#include "game.h"
#include "tools.h"

#include "intro.h"
#include "welcome.h"
#include "arrange.h"
#include "shooting.h"
#include "end.h"

#include <array>
#include <algorithm>
#include <string>

using std::array, std::max, std::string;

Game::Game()
{
    srand(time(0));
    _state = GameStates::INTRO;
    _play();
}

void Game::setCurrPlayer(Player* p)
{
    _currPlayer = p;
}

void Game::setCurrEnemy(Player* p)
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

bool Game::isHvsH()
{
    return getCurrPlayer()->getType() == PlayerTypes::HUMAN
        && getCurrEnemy()->getType() == PlayerTypes::HUMAN;
}

void Game::changePlayers()
{
    Player* player = Game::getCurrPlayer();
    Game::setCurrPlayer(Game::getCurrEnemy());
    Game::setCurrEnemy(player);
}

int Game::getPlayerPoints(int pIdx)
{
    if (pIdx < _points.size()) {
        return _points[pIdx];
    }
    else return 0;
}

void Game::addPoint(Player* p)
{
    _points[p->getId()] += 1;
}

int Game::getTime()
{
    return time(0) - _timer;
}

void Game::_play()
{
    while (true) {
        Tools::clearConsole();

        switch(_state)
        {
        case GameStates::INTRO:
            {
            Intro* screen = new Intro();
            _setScreen(screen);

            _screen->update();

            _state = GameStates::WELCOME;
            } break;
        case GameStates::WELCOME:
            {
            Welcome* screen = new Welcome();
            _setScreen(screen);

            screen->update();

            _state = GameStates::ARRANGE;
            } break;
        case GameStates::ARRANGE:
            {
            Arrange* screen = new Arrange();
            _setScreen(screen);

            _timer = time(0);
            screen->update();

            _state = GameStates::SHOOTING;
            } break;
        case GameStates::SHOOTING:
            {
            Shooting* screen = new Shooting();
            _setScreen(screen);

            screen->update();

            _state = GameStates::END;
            } break;
        case GameStates::END:
            {
            End* screen = new End();
            _setScreen(screen);

            screen->update();

            if (screen->isPlayAgain()) {
                _state = GameStates::WELCOME;
            }
            else exit(0);
            } break;
        }
    }
}

void Game::_setScreen(Screen *screen)
{
    delete _screen;
    _screen = screen;
}
