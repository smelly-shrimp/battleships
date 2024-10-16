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
    // Fman::playAnim("arrange", false, false);
}

void Arrange::inputShips()
{
    string ans = _console.input("To position: <a-j><1-10>");
    regex re{"[a-j][0-9]{1,2}"};

    if (regex_match(ans, re)) {
        string anst{ans};
        int x = stoi(anst.erase(0, 1));
        if (x <= 0 || x > 10) _askAgain();

        _x = x - 1;
        _y = int(tolower(ans.at(0))) - 97;

        Game::getCurrPlayer()->grid.setSquare(_x, _y, 1);
        _printList();
        _printGrid();
    }
    else _askAgain();
}

void Arrange::_printList()
{
    Tools::clearConsole();
    cout << Game::getCurrPlayer()->grid.getShipList();
    // cout << "4 × single-masted __ __ __ __" << endl;
    // cout << "3 × two-masted    __ __ __" << endl;
    // cout << "2 × three-masted  __ __" << endl;
    // cout << "1 × four-masted   __" << endl;
    // cout << endl;
}

void Arrange::_askAgain()
{
    print();
    _console.drawError("You're stupid!");
    print();
    inputShips();
}

void Arrange::_printGrid()
{
    cout << Game::getCurrPlayer()->grid.getGrid();
    cout << "\n\n";
}
