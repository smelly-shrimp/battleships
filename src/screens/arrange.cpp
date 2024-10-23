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
    auto grid{Game::getCurrPlayer()->grid};
    array<string, 4> names{ "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    _console.drawHeader(format("ARRANGING {}", Game::getCurrPlayer()->getName()), true);

    int curr{};
    for (int i{}; i < names.size(); i++) {
        cout << Tools::insertChars(" ", 2) << names.at(i) << " ";

        for (int j{}; j <= i && curr < grid.getShipList().size(); j++) {
            cout << (grid.getShipList().at(curr)->isUsed() ? "██ " : "▁▁ ");
            curr++;
        }

        cout << "\n";
    }

    cout << "\n";

    cout << Tools::insertChars(" ", 2) << "┌───┬───────── OCEAN GRID ──────────┐\n"
         << Tools::insertChars(" ", 2) << "│   │ 01 02 03 04 05 06 07 08 09 10 │\n"
         << Tools::insertChars(" ", 2) << "├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤\n";

    for (int i{}; i < grid.getGrid().size(); i++) {
        cout << Tools::insertChars(" ", 2) << "│ " << char(65 + i) << " ┼ ";

        for (int j{}; j < grid.getGrid().size(); j++) {
            cout << grid.asString(grid.getSquare(i, j));
        }

        cout << "│\n";
    }

    cout << Tools::insertChars(" ", 2) << "└" << Tools::insertChars("─", 35) << "┘\n";
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
            Game::getCurrPlayer()->grid.setCurrShip(curr);
            arrangeMode == Mode::MANUAL ? _selectShipPos() : _autoSelectShipPos();
            curr++;
        }
        _len--;
    }

    if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
        for (int i{}; i < 10; i++) {
            for (int j{}; j < 10; j++) {
                cout << Game::getCurrPlayer()->grid.getGrid()[i][j];
            }
        }
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

        if (!Game::getCurrPlayer()->grid.isAvailable(row, col, _len, orient)) {
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

    if (!Game::getCurrPlayer()->grid.isAvailable(row, col, _len, orient)) {
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
    for (int i{}; i < _len; i++) {
        Game::getCurrPlayer()->grid.setSquare(
            (orient == 0 ? row : row + i), (orient == 0 ? col + i : col),
            Game::getCurrPlayer()->grid.getCurrShip()->getId()
        );

        Game::getCurrPlayer()->grid.setOccup(row, col, _len, orient);
    }
}

void Arrange::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
}
