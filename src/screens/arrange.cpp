#include <iostream>
#include <array>
#include <format>
#include <regex>
#include "arrange.h"
#include "fman.h"
#include "game.h"
#include "tools.h"

using std::cout, std::array, std::string, std::format, std::stoi, std::regex, std::smatch;

Arrange::Arrange()
{
    srand(time(0));
}

void Arrange::print()
{
    _console.drawShipList(format("ARRANGING {}", Game::getCurrPlayer()->getName()), true);
    _console.drawGrid(true);
}

Mode Arrange::selectArrangeMode()
{
    print();
    string ans = Tools::lower(_console.input("To arrange: manual => M; automatic => A"));

    if (_console.isAnswer(ans, "(m|manual)")) return Mode::MANUAL;
    else if (_console.isAnswer(ans, "(a|auto|automatic)")) return Mode::AUTO;
    else {
        _askAgain(format("There's no such mode as {}!", ans));
        selectArrangeMode();
        // return 0;
    }

    return Mode::MANUAL;
}

void Arrange::selectShip(Mode arrangeMode)
{
    _len = 4;
    int curr{};
    for (int i{}; i < 4; i++) {
        for (int j{}; j <= i; j++) {
            Game::getCurrPlayer()->grid->setCurrShip(curr);
            arrangeMode == Mode::MANUAL ? _selectShipPos() : _autoSelectShipPos();
            curr++;
        }
        _len--;
    }

    if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
        // for (int i{}; i < 10; i++) {
        //     for (int j{}; j < 10; j++) {
        //         cout << Game::getCurrPlayer()->grid.getGrid()[i][j];
        //     }
        // }
        print();
        _console.drawInfo("You've just arranged all of your ships!");
    }
    
    Game::changePlayers();
}

void Arrange::_selectShipPos()
{
    print();
    string ans = _console.input(format("To position: <a-j><1-10> {}", _len > 1 ? "<(h)orizontal/(v)ertical>" : ""));

    regex re("(([a-j])([1-9]|10)) (h|v)");
    smatch matches;

    if (regex_match(ans, matches, re)) {
        int row{int(tolower(matches[2].str().c_str()[0])) - 97};
        int col{stoi(matches[3].str().c_str()) - 1};
        int orient{};
        
        if (_len > 1) orient = _setOrient(matches);

        if (!Game::getCurrPlayer()->grid->isAvailable(row, col, _len, orient)) {
            _askAgain("Wrong or occupied position!");
            _selectShipPos();
            return;
        }

        _createShip(row, col, orient);
    }
    else {
        _askAgain("Wrong position!");
        _selectShipPos();
    }
}

void Arrange::_autoSelectShipPos()
{
    int row{rand() % 10};
    int col{rand() % 10};
    int orient{rand() % 2};

    if (!Game::getCurrPlayer()->grid->isAvailable(row, col, _len, orient)) {
        _autoSelectShipPos();
        return;
    }

    _createShip(row, col, orient);
}

int Arrange::_setOrient(smatch matches)
{
    regex reh("(h|horizontal)");
    regex rev("(v|vertical)");

    if (regex_match(matches[4].str(), reh)) return 0;
    else if (regex_match(matches[4].str(), rev)) return 1;
    else {
        _askAgain("Wrong rotation!");
        _selectShipPos();
    }

    return 0;
}

void Arrange::_createShip(int row, int col, int orient)
{
    auto grid{Game::getCurrPlayer()->grid};
    for (int i{}; i < _len; i++) {
            grid->setSquare(
            (orient == 0 ? row : row + i), (orient == 0 ? col + i : col),
            grid->getCurrShip()->getId()
        );
        grid->getCurrShip()->setPos(row, col);
        grid->getCurrShip()->setOrient(orient);
        grid->setOccup(row, col, _len, orient);
    }
}

void Arrange::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
}
