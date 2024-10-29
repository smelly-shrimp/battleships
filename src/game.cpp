#include <iostream>
#include "game.h"
#include "intro.h"
#include "welcome.h"
#include "arrange.h"
#include "shooting.h"
#include "tools.h"
#include "player.h"
#include "end.h"

using std::cout;

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
    Player* p1{};
    Player* p2{};

    while (true) {
        Tools::clearConsole();

        switch(_state)
        {
        case INTRO:
            {
            Intro* screen = new Intro();
            setScreen(screen);

            _screen->print();
            _state = GameStates::WELCOME;
            break;
            }
        case WELCOME:
            {
            Welcome* screen = new Welcome();
            setScreen(screen);

            p1 = new Human("PLAYER_1", PlayerTypes::HUMAN);
            setCurrPlayer(p1);

            p2 = screen->selectEnemy();
            setCurrEnemy(p2);

            _state = GameStates::ARRANGE;
            break;
            }
        case ARRANGE:
            {
            Arrange* screen = new Arrange();
            setScreen(screen);
                
            for (int i{}; i < 2; i++) {
                if (getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
                    screen->selectShip(screen->selectArrangeMode());
                }
                else screen->selectShip(Mode::AUTO);
            }

            _state = GameStates::SHOOTING;
            break;
            }
        case SHOOTING:
            {
            Shooting* screen = new Shooting();
            setScreen(screen);

            while (true) {
                if (screen->selectShot() == 1) break;
            }
            _state = GameStates::END;
            break;
            }
        case END:
            {
            End* screen = new End();
            setScreen(screen);

            screen->print();
            if (screen->isPlayAgain()) {
                _state = GameStates::WELCOME;
            }
            else exit(0);
            break;
            }
        default:
            cout << Tools::ft["red"] << "PANIC! ILLEGAL STATE! STOPPING EXECUTION!" << Tools::ft["endf"] << "\n";
            exit(0);
        }
    }
}

inline void Game::setScreen(Screen *screen)
{
    delete _screen;
    _screen = screen;
}
