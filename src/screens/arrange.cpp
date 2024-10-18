#include <iostream>
#include <regex>
#include "arrange.h"
#include "fman.h"
#include "game.h"
#include "tools.h"

using namespace std;

void Arrange::print()
{
    cout << Game::getCurrPlayer()->grid.getShipList();
    cout << Game::getCurrPlayer()->grid.getGrid();
    cout << "\n\n";
}

void Arrange::inputShip()
{
    int len = 4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 1; j++) {
            _inputShipPos();
            if (len > 1) _inputShipRot(len);
            else _createShip(len);
        }
        len -= 1;
    }
}

void Arrange::_inputShipPos()
{
    string ans = _console.input("To position: <a-j><1-10>", Game::getCurrPlayer()->getName());
    // regex re{"[a-j][0-9]{1,2}"};
    regex re{"[a-j]([1-9]|10)"};

    if (regex_match(ans, re)) {
        string anst{ans};
        int x = stoi(anst.erase(0, 1));
        if (x <= 0 || x > 10) _askAgain();

        _x = x - 1;
        _y = int(tolower(ans.at(0))) - 97;
    }
    else _askAgain();

    print();
}

void Arrange::_inputShipRot(int length)
{
    string ans = _console.input("To rotation: <(h)orizontal/(v)>ertical", Game::getCurrPlayer()->getName());
    ans = Tools::lower(ans);

    if (_console.isAnswer(ans, "(h|horizontal)") || _console.isAnswer(ans, "(v|vertical)")) {
        if (_console.isAnswer(ans, "(h|horizontal)")) _rotation = 0;
        else _rotation = 1;

        _createShip(length);
    }
    else {
        _console.drawError("Wrong rotation!");
        print();
        _inputShipRot(length);
    }
}

void Arrange::_createShip(int length)
{
    Game::getCurrPlayer()->grid.setShip(_x, _y, _rotation, 1, length);
    print();
}

void Arrange::_askAgain()
{
    print();
    _console.drawError("You're stupid!");
    print();
    _inputShipPos();
}
