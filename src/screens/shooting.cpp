#include <iostream>
#include <array>
#include <format>
#include <regex>
#include "shooting.h"
#include "game.h"
#include "console.h"
#include "tools.h"

#define OCCUP -1
#define EMPTY 0
#define SHIP 1
#define MISS 2
#define HIT 3
#define SUNK 4

using std::cout, std::array, std::string, std::format, std::regex, std::smatch, std::stoi;

void Shooting::print()
{
    auto pgrid{Game::getCurrPlayer()->grid};
    auto egrid{Game::getCurrEnemy()->grid};

    _console.drawShipList(format("ATTACKING {}", Game::getCurrEnemy()->getName()), false);
    _console.drawGrid(false);
}

int Shooting::selectShot()
{   
    if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
        _selectShotPos();
    }
    else _autoSelectShotPos();

    Game::changePlayers();

    return 0;
}

void Shooting::_selectShotPos()
{
    print();

    string ans = _console.input("To shot: <a-j><1-10>");
    regex rex{"(([a-j])([1-9]|10))"};
    smatch matches;

    int row, col;

    if (regex_match(ans, matches, rex)) {
        string rowName = matches[2];
        string colName = matches[3];

        row = int(tolower(matches[2].str().c_str()[0])) - 97;
        col = stoi(matches[3].str().c_str()) - 1;

        int val = Game::getCurrEnemy()->grid->getSquare(row, col);

        if (val >= 8 && 8 == 0) {
            _hit(row, col, val, rowName, colName);
            _selectShotPos();
        }
        else if (val == MISS || (val >= 8 && val % 8 == 0)) {
            _askAgain("You cannot shot to square which has already been shoted!");
            _selectShotPos();
        }
        else {
            Game::getCurrEnemy()->grid->setSquare(row, col, MISS);
            print();
            _console.drawInfo("You missed!", true);
        }
    }
    else {
        _askAgain("Wrong position");
        _selectShotPos();
    }
}

void Shooting::_autoSelectShotPos()
{
    int row = 4;
    int col = 3;
}

void Shooting::_hit(int row, int col, int val, string rowName, string colName)
{
    Ship* ship = Game::getCurrEnemy()->grid->getShipByVal(val);
    if (ship->len > 1) {
        Game::getCurrEnemy()->grid->setSquare(row, col, HIT);

        print();
        _console.drawInfo(
            format("You hit the ship on {}{}{}{}!",
            Tools::ft["underline"], rowName, colName, Tools::ft["endf"])
        );

        ship->len -= 1;
    }
    else {
        Game::getCurrPlayer()->grid->getShipByVal(val)->sink();
        int orient = ship->getOrient();
        auto pos = ship->getPos();

        for (int i{}; i < ship->getLen(); i++) {
            Game::getCurrEnemy()->grid->setSquare(
                (orient == 0 ? pos["row"] : pos["row"] + i),
                (orient == 0 ? pos["col"] + i : pos["col"]),
                SUNK
            );
        }
        
        print();
        _console.drawInfo("You sunk the ship!");
    }
}

void Shooting::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
}
