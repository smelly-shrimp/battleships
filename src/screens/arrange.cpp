#include <iostream>
#include <format>
#include <regex>
#include <string>
#include "tools.h"

#include "arrange.h"
#include "game.h"

using std::format, std::regex, std::smatch, std::stoi, std::string;

Arrange::Arrange()
{
    srand(time(0));
}

void Arrange::print()
{
    _console.drawShipList(format("ARRANGING {}", Game::getCurrPlayer()->getName()), true);
    _console.drawGrid(true, false);
}

Mode Arrange::selectArrangeMode()
{
    print();
    string ans{Tools::lower(_console.input("To arrange: manual => M; automatic => A"))};

    if (_console.isAnswer(ans, "(m|manual)")) return Mode::MANUAL;
    else if (_console.isAnswer(ans, "(a|auto|automatic)")) return Mode::AUTO;
    else {
        print();
        _console.drawError(format("There's no such mode as {}!", ans));
        return selectArrangeMode();
    }
}

void Arrange::selectShip(Mode mode)
{
    int len{4};
    int curr{};
    for (int i{}; i < 4; i++) {
        for (int j{}; j <= i; j++) {
            Game::getCurrPlayer()->grid->setCurrShip(curr);
            ShipPos shipPos{mode == Mode::MANUAL ? _selectShipPos(len) : _autoSelectShipPos(len)};
            _createShip(shipPos, len);
            
            curr++;
        }
        len--;
    }

    if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
        print();
        _console.drawInfo("You've just arranged all of your ships!");

        if (Game::getCurrEnemy()->getType() == PlayerTypes::HUMAN) {
            _console.drawShipList("", true, true);
            _console.drawGrid(true, false, true);
            _console.drawInfo("...");
        }
    }
    
    Game::changePlayers();
}

ShipPos Arrange::_selectShipPos(int len)
{
    print();
    string ans{_console.input(format("To position: <a-j><1-10> {}", len > 1 ? "<(h)orizontal/(v)ertical>" : ""))};

    regex re("(([a-j])([1-9]|10)) (h|v)");
    smatch matches{};
    int row{}, col{};
    int orient{};

    if (regex_match(ans, matches, re)) {
        row = int(tolower(matches[2].str().c_str()[0])) - 97;
        col = stoi(matches[3].str().c_str()) - 1;

        if (len > 1) {
            regex reh("(h|horizontal)");
            regex rev("(v|vertical)");
            if (regex_match(matches[4].str(), reh)) orient = 0;
            else orient = 1;
        }

        if (!Game::getCurrPlayer()->grid->isAvailable(row, col, len, orient)) {
            print();
            _console.drawError("Wrong or occupied position!");
            return _selectShipPos(len);
        }

        return {row, col, orient};
    }
    else {
        print();
        _console.drawError(format("Wrong position", ans));
        return _selectShipPos(len);
    }
}

ShipPos Arrange::_autoSelectShipPos(int len)
{
    int row{rand() % 10};
    int col{rand() % 10};
    int orient{rand() % 2};

    if (!Game::getCurrPlayer()->grid->isAvailable(row, col, len, orient)) {
        return _autoSelectShipPos(len);
    }

    return {row, col, orient};
}

void Arrange::_createShip(ShipPos& pos, int len)
{
    Grid* grid{Game::getCurrPlayer()->grid};
    for (int i{}; i < len; i++) {
            grid->setSquare(
            (pos.orient == 0 ? pos.row : pos.row + i), (pos.orient == 0 ? pos.col + i : pos.col),
            grid->getCurrShip()->getId()
        );
    }

    grid->getCurrShip()->use();
    grid->getCurrShip()->setPos(pos.row, pos.col);
    grid->getCurrShip()->setLen(len);
    grid->getCurrShip()->setOrient(pos.orient);
    grid->setOccup(pos.row, pos.col, len, pos.orient, -1);
}
