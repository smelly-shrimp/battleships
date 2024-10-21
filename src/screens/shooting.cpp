#include <iostream>
#include <regex>
#include "shooting.h"
#include "game.h"
#include "console.h"

using std::cout, std::string, std::regex, std::smatch, std::stoi;

void Shooting::print()
{
    cout << Game::getCurrPlayer()->grid.getShipList();
    cout << Game::getCurrPlayer()->grid.reload();
}

void Shooting::selectShot()
{
    _selectShotPos();
}

void Shooting::_selectShotPos()
{
    // print();

    string ans = _console.input("To shot: <a-j><1-10>", Game::getCurrPlayer()->getName());

    regex rex{"(([a-j])([1-9]|10))"};
    smatch matches;

    if (regex_match(ans, matches, rex)) {
        int col = stoi(matches[3].str().c_str()) - 1;
        int row = int(tolower(matches[2].str().c_str()[0])) - 97;

        // print();
        cout << Game::getCurrPlayer()->getName() << "\n";
        switch (Game::getCurrEnemy()->grid.getSquare(col, row))
        {
            case 1:
                Game::getCurrPlayer()->grid.setSquare(col, row, 2);
                Game::getCurrEnemy()->grid.setSquare(col, row, 3);
                _console.drawInfo("You hit a ship!");
                _selectShotPos();
                break;
            case -2:
                _console.drawError("This square has been already been shoted!");
                _selectShotPos();
                break;
            default:
                Game::getCurrPlayer()->grid.setSquare(col, row, -2);
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
    // print();
    _console.drawError(msg);
    // print();
}
