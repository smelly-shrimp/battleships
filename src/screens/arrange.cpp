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
    _console.drawGrid(true);
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
        grid->getCurrShip()->setPos(pos.row, pos.col);
        grid->getCurrShip()->setOrient(pos.orient);
        grid->setOccup(pos.row, pos.col, len, pos.orient);
    }
}

// int Arrange::_selectOrient(std::smatch matches)
// {
//     regex reh("(h|horizontal)");
//     regex rev("(v|vertical)");

//     if (regex_match(matches[4].str(), reh)) return 0;
//     else if (regex_match(matches[4].str(), rev)) return 1;
//     else {
//         print();
//         _console.drawError("Wrong rotation!");
//         return _selectShipPos();
//     }
// }

// #include <iostream>
// #include <array>
// #include <format>
// #include <regex>
// #include "arrange.h"
// #include "fman.h"
// #include "game.h"
// #include "tools.h"

// using std::cout, std::array, std::string, std::format, std::stoi, std::regex, std::smatch;

// Arrange::Arrange()
// {
//     srand(time(0));
// }

// void Arrange::print()
// {
//     _console.drawShipList(format("ARRANGING {}", Game::getCurrPlayer()->getName()), true);
//     _console.drawGrid(true);
// }

// Mode Arrange::selectArrangeMode()
// {
//     print();
//     string ans = Tools::lower(_console.input("To arrange: manual => M; automatic => A"));

//     if (_console.isAnswer(ans, "(m|manual)")) return Mode::MANUAL;
//     else if (_console.isAnswer(ans, "(a|auto|automatic)")) return Mode::AUTO;
//     else {
//         _askAgain(format("There's no such mode as {}!", ans));
//         selectArrangeMode();
//     }

//     return Mode::MANUAL;
// }

// void Arrange::selectShip(Mode arrangeMode)
// {
//     _len = 4;
//     int curr{};
//     for (int i{}; i < 4; i++) {
//         for (int j{}; j <= i; j++) {
//             Game::getCurrPlayer()->grid->setCurrShip(curr);
//             arrangeMode == Mode::MANUAL ? _selectShipPos() : _autoSelectShipPos();
//             curr++;
//         }
//         _len--;
//     }

//     if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
//         print();
//         _console.drawInfo("You've just arranged all of your ships!");
//     }
    
//     Game::changePlayers();
// }

// void Arrange::_selectShipPos()
// {
//     print();
//     string ans = _console.input(format("To position: <a-j><1-10> {}", _len > 1 ? "<(h)orizontal/(v)ertical>" : ""));

//     regex re("(([a-j])([1-9]|10)) (h|v)");
//     smatch matches;

//     if (regex_match(ans, matches, re)) {
//         int row{int(tolower(matches[2].str().c_str()[0])) - 97};
//         int col{stoi(matches[3].str().c_str()) - 1};
//         int orient{};
        
//         if (_len > 1) orient = _setOrient(matches);

//         if (!Game::getCurrPlayer()->grid->isAvailable(row, col, _len, orient)) {
//             _askAgain("Wrong or occupied position!");
//             _selectShipPos();
//             return;
//         }

//         _createShip(row, col, orient);
//     }
//     else {
//         _askAgain("Wrong position!");
//         _selectShipPos();
//     }
// }

// void Arrange::_autoSelectShipPos()
// {
//     int row{rand() % 10};
//     int col{rand() % 10};
//     int orient{rand() % 2};

//     if (!Game::getCurrPlayer()->grid->isAvailable(row, col, _len, orient)) {
//         _autoSelectShipPos();
//         return;
//     }

//     _createShip(row, col, orient);
// }

// int Arrange::_setOrient(smatch matches)
// {
//     regex reh("(h|horizontal)");
//     regex rev("(v|vertical)");

//     if (regex_match(matches[4].str(), reh)) return 0;
//     else if (regex_match(matches[4].str(), rev)) return 1;
//     else {
//         _askAgain("Wrong rotation!");
//         _selectShipPos();
//     }

//     return 0;
// }

// void Arrange::_createShip(int row, int col, int orient)
// {
//     auto grid{Game::getCurrPlayer()->grid};
//     for (int i{}; i < _len; i++) {
//             grid->setSquare(
//             (orient == 0 ? row : row + i), (orient == 0 ? col + i : col),
//             grid->getCurrShip()->getId()
//         );
//         grid->getCurrShip()->setPos(row, col);
//         grid->getCurrShip()->setOrient(orient);
//         grid->setOccup(row, col, _len, orient);
//     }
// }

// void Arrange::_askAgain(string msg)
// {
//     print();
//     _console.drawError(msg);
// }
