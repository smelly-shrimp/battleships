#include <iostream>
#include <format>
#include <regex>
#include "shooting.h"
#include "game.h"
#include "console.h"
#include "tools.h"

#define SHIP 1
#define HIT 2
#define MISS 3

using std::cout, std::string, std::format, std::regex, std::smatch, std::stoi;

void Shooting::print()
{
    _console.drawHeader(format("ATTACKING {}", Game::getCurrEnemy()->getName()), true);
    cout << Game::getCurrPlayer()->grid.getShipList();
    cout << Game::getCurrPlayer()->grid.reload();
}

void Shooting::selectShot()
{
    _selectShotPos();
}

void Shooting::_selectShotPos()
{
    string ans = _console.input("To shot: <a-j><1-10>");

    regex rex{"(([a-j])([1-9]|10))"};
    smatch matches;

    if (regex_match(ans, matches, rex)) {
        string colNe = matches[3];
        string rowNe = matches[2];
        int col = stoi(matches[3].str().c_str()) - 1;
        int row = int(tolower(matches[2].str().c_str()[0])) - 97;

        switch (Game::getCurrEnemy()->grid.getSquare(col, row))
        {
            case SHIP:
                // Game::getCurrPlayer()->grid.setSquare(col, row, 2);
                // Game::getCurrEnemy()->grid.setSquare(col, row, 3);
                _console.drawInfo(format("You hit a ship on {}{}{}{}!", Tools::ft["underline"], rowNe, colNe, Tools::ft["endf"]));
                _selectShotPos();
                break;
            // case MISS:
            //     _console.drawError("This square has been already been shoted!");
                // _askAgain(format("This square has been already been shoted!"));
            //     _selectShotPos();
                // break;
            default:
                // Game::getCurrPlayer()->grid.setSquare(col, row, MISS);
                _console.drawInfo("You missed!");
                break;
        }
    }
    else {
        _askAgain("Wrong position");
        _selectShotPos();
    }
}

void Shooting::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
}
