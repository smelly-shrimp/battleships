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

    _console.drawHeader("ARRANGE", true);

    int curr{};
    for (int i{}; i < names.size(); i++) {
        cout << Tools::insertChars(" ", 8) << names.at(i) << " ";

        for (int j{}; j <= i && curr < grid.getShipList().size(); j++) {
            cout << (grid.getShipList().at(curr)->isUsed() ? "██" : "▁▁");
            curr++;
        }

        cout << "\n";
    }

    cout << "\n";

    cout << Tools::insertChars(" ", 8) << "========== OCEAN GRID =========\n"
         << Tools::insertChars(" ", 8) << ". 01 02 03 04 05 06 07 08 09 10\n";

    for (int i{}; i < grid.getGrid().size(); i++) {
        cout << Tools::insertChars(" ", 8) << char(65 + i) << " ";

        for (int j{}; j < grid.getGrid().size(); j++) {
            cout << grid.asString(grid.getSquare(i, j));
        }

        cout << "\n";
    }

    cout << "\n";
}

int Arrange::selectArrangeMode()
{
    print();
    string ans = Tools::lower(_console.input("To arrange: manual => M; automatic => A"));

    if (_console.isAnswer(ans, "(m|manual)")) return 0;
    else if (_console.isAnswer(ans, "(a|auto|automatic)")) return 1;
    else {
        _askAgain(format("There's no such mode as {}!", ans));
        selectArrangeMode();
    }

    return 0;
}

void Arrange::selectShip(int arrangeMode)
{
    _len = 4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 1; j++) {
            arrangeMode == 0 ? _selectShipPos() : _autoSelectShipPos();
        }
        _len -= 1;
    }

    if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
        print();
        _console.drawInfo("You've just arranged all of your ships!");
    }
    Game::changePlayers();
}

void Arrange::_selectShipPos()
{
    print();
    string ans = _console.input(format("To position: <a-j><1-10> {}", _len > 1 ? "<(h)orizontal/(v)ertical>" : ""));

    regex ren("(([a-j])([1-9]|10)) (h|v)");
    regex rex("(([a-j])([1-9]|10))");
    smatch matches;

    if (regex_match(ans, matches, (_len > 1 ? ren : rex))) {
        int col{stoi(matches[3].str().c_str()) - 1};
        int row{int(tolower(matches[2].str().c_str()[0])) - 97};
        int orient{};
        
        if (_len > 1) orient = _setOrient(matches);

        // if (!Game::getCurrPlayer()->grid.isAvaible(col, row, _len, orient)) {
        //     _askAgain("Wrong or occupied position");
        //     _selectShipPos();
        //     return;
        // }

        // Game::getCurrPlayer()->grid.createShip(col, row, _len, orient, 1);
    }
    else {
        _askAgain("Wrong position!");
        _selectShipPos();
    }
}

void Arrange::_autoSelectShipPos()
{
    int col{rand() % 10};
    int row{rand() % 10};
    int orient{rand() % 2};

    // if (!Game::getCurrPlayer()->grid.isAvaible(col, row, _len, orient)) {
    //     _autoSelectShipPos();
    //     return;
    // }

    // Game::getCurrPlayer()->grid.createShip(col, row, _len, orient, 1);
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

void Arrange::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
}
