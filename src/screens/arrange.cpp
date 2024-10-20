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
    cout << endl << endl;
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
        int y = int(tolower(matches[2].str().c_str()[0])) - 97;
        int x = stoi(matches[3].str().c_str()) - 1;
        int orient = 0;
        
        if (_len > 1) orient = _setOrient(matches);

        if (!Game::getCurrPlayer()->grid.isAvaible(x, y, _len, orient)) {
            _askAgain("Wrong or occupied position");
            _inputShipPos();
            return;
        }

        _createShip(x, y, orient);
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

void Arrange::_createShip(int x, int y, int orient)
{
    Game::getCurrPlayer()->grid.setShip(x, y, _len, orient, 1);
    print();
}

void Arrange::_askAgain(string msg)
{
    _console.drawError(msg);
    print();
}
