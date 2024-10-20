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
}

void Arrange::inputShip()
{
    _len = 4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 1; j++) {
            _inputShipPos();
        }
        _len -= 1;
    }
}

void Arrange::_inputShipPos()
{
    string ans = _console.input(
        string("To position: <a-j><1-10>") + (_len > 1 ? " <(h)orizontal/(v)ertical>" : ""),
        Game::getCurrPlayer()->getName()
    );

    regex ren("(([a-j])([1-9]|10)) (h|v)");
    regex rex("(([a-j])([1-9]|10))");

    smatch matches;
    if (regex_match(ans, matches, (_len > 1 ? ren : rex))) {
        int col = stoi(matches[3].str().c_str()) - 1;
        int row = int(tolower(matches[2].str().c_str()[0])) - 97;
        int orient = 0;
        
        if (_len > 1) orient = _setOrient(matches);

        if (!Game::getCurrPlayer()->grid.isAvaible(col, row, _len, orient)) {
            _askAgain("Wrong or occupied position");
            _inputShipPos();
            return;
        }

        _createShip(col, row, orient);
    }
    else {
        _askAgain("Wrong position!");
        _inputShipPos();
    }
}

int Arrange::_setOrient(smatch matches)
{
    regex reh("(h|horizontal)");
    regex rev("(v|vertical)");

    if (regex_match(matches[4].str(), reh)) return 0;
    else if (regex_match(matches[4].str(), rev)) return 1;
    else {
        _askAgain("Wrong rotation!");
        _inputShipPos();
    }

    return 0;
}

void Arrange::_createShip(int col, int row, int orient)
{
    Game::getCurrPlayer()->grid.setShip(col, row, _len, orient, 1);
    print();
}

void Arrange::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
    print();
}
