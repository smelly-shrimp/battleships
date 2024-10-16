#include <iostream>
#include <regex>
#include "arrange.h"
#include "fman.h"
#include "game.h"
#include "tools.h"

using namespace std;

void Arrange::print()
{
    _printList();
    _printGrid();
}

void Arrange::inputShipPos()
{
    string ans = _console.input("To position: <a-j><1-10>");
    regex re{"[a-j][0-9]{1,2}"};

    if (regex_match(ans, re)) {
        string anst{ans};
        int x = stoi(anst.erase(0, 1));
        if (x <= 0 || x > 10) _askAgain();

        _x = x - 1;
        _y = int(tolower(ans.at(0))) - 97;
    }
    else _askAgain();
}

void Arrange::inputShipRot()
{
    string ans = _console.input("To rotation: <(h)orizontal/(v)>ertical");
    ans = Tools::lower(ans);
    print();

    if (_console.isAnswer(ans, "(h|horizontal)") || _console.isAnswer(ans, "(v|vertical)")) {
        Game::getCurrPlayer()->grid.setShip(_x, _y, _rotation, 1);
        _printList();
        _printGrid();

        if (_console.isAnswer(ans, "(h|horizontal)")) _rotation = 0;
        else if (_console.isAnswer(ans, "(v|vertical)")) _rotation = 1;
    }
    else {
        _console.drawError("Wrong rotation!");
        print();
        inputShipRot();
    }
}

void Arrange::_printList()
{
    Tools::clearConsole();
    cout << Game::getCurrPlayer()->grid.getShipList();
}

void Arrange::_askAgain()
{
    print();
    _console.drawError("You're stupid!");
    print();
    inputShipPos();
}

void Arrange::_printGrid()
{
    cout << Game::getCurrPlayer()->grid.getGrid();
    cout << "\n\n";
}
