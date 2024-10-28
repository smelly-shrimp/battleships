#include <format>
#include <regex>
#include <string>
#include "shooting.h"
#include "game.h"

using std::regex, std::smatch, std::stoi, std::string;

Shooting::Shooting()
{
    srand(time(0));
}

void Shooting::print()
{
    _console.drawShipList(format("ATTACKING {}",
        Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN ?
          Game::getCurrEnemy()->getName()
        : Game::getCurrPlayer()->getName()), false);
    _console.drawGrid(false, Game::getCurrPlayer()->getType() == PlayerTypes::COMP);
}

int Shooting::selectShot()
{
    while (true) {
        if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
            _selectShotPos();
            if (Game::getCurrEnemy()->getType() == PlayerTypes::HUMAN) {
                _console.drawShipList("", true, true);
                _console.drawGrid(false, false, true);
                _console.drawInfo("...");
            }
        }
        else _autoSelectShotPos();

        Game::changePlayers();
    }
}

void Shooting::_selectShotPos()
{
    print();
    string ans = _console.input("To shot: <a-j><1-10>");

    regex re{"(([a-j])([1-9]|10))"};
    smatch matches;
    int row{}, col{};

    if (regex_match(ans, matches, re)) {
        row = int(tolower(matches[2].str().c_str()[0])) - 97;
        col = stoi(matches[3].str().c_str()) - 1;

        ShotPos pos{row, col};

        switch (checkReaction(pos))
        {
        case Reactions::HIT:
            print();
            _console.drawInfo("You hit a ship!");
            _selectShotPos();
            break;
        case Reactions::SUNK:
            print();
            _console.drawInfo("You sunk a ship!");
            _selectShotPos();
            break;
        case Reactions::AGAIN:
            print();
            _console.drawInfo("You cannot hit ship twice!");
            _selectShotPos();
            break;
        case Reactions::MISS:
            print();
            _console.drawInfo("You missed!", true);
            break;
        default:
        }
    }
    else {
        print();
        _console.drawError(format("Wrong position", ans));
        return _selectShotPos();
    }
}

void Shooting::_autoSelectShotPos()
{
    int row{rand() % 10};
    int col{rand() % 10};
    ShotPos pos{row, col};

    switch (checkReaction(pos))
    {
    case Reactions::HIT:
        print();
        _console.drawInfo("Comp hit your ship!", true);
        _autoSelectShotPos();
        break;
    case Reactions::SUNK:
        print();
        _console.drawInfo("Comp sunk your ship!", true);
        _autoSelectShotPos();
        break;
    case Reactions::AGAIN:
        _autoSelectShotPos();
        break;
    case Reactions::MISS:
        print();
        _console.drawInfo("Comp missed!");
        break;
    default:
    }
}

Reactions Shooting::checkReaction(ShotPos& pos)
{
    int val{Game::getCurrEnemy()->grid->getSquare(pos.row, pos.col)};
    Ship* ship{Game::getCurrEnemy()->grid->getShipByVal(val)};
    Grid* grid{Game::getCurrEnemy()->grid};

    if (val >= 8 && val % 8 == 0) {
        ship->hit();

        if (ship->isSink()) {
            auto spos{ship->getPos()};
            int orient{ship->getOrient()};
            for (int i{}; i < ship->getLen(); i++) {
                grid->setSquare(
                    (orient == 0 ? spos["row"] : spos["row"] + i),
                    (orient == 0 ? spos["col"] + i : spos["col"]),
                    static_cast<int>(SquareValues::SUNK));
            }

            Game::getCurrEnemy()->grid->setOccup(spos["row"], spos["col"], ship->getLen(), orient, -2);
            return Reactions::SUNK;
        }
        else {
            grid->setSquare(pos.row, pos.col, static_cast<int>(SquareValues::HIT));
            return Reactions::HIT;
        }
    }
    else if (val == static_cast<int>(SquareValues::MISS)
          || val == static_cast<int>(SquareValues::HIT)
          || val == static_cast<int>(SquareValues::SUNK)) {
        return Reactions::AGAIN;
    }
    else {
        grid->setSquare(pos.row, pos.col, static_cast<int>(SquareValues::MISS));
        return Reactions::MISS;
    }
}

// #include <iostream>
// #include <array>
// #include <format>
// #include <regex>
// #include "shooting.h"
// #include "game.h"
// #include "console.h"
// #include "tools.h"

// using std::cout, std::array, std::string, std::stoi, std::format, std::regex, std::smatch, std::stoi;

// Shooting::Shooting()
// {
//     srand(time(0));
// }

// void Shooting::print()
// {
//     auto pgrid{Game::getCurrPlayer()->grid};
//     auto egrid{Game::getCurrEnemy()->grid};

//     _console.drawShipList(format("ATTACKING {}", Game::getCurrEnemy()->getName()), false);
//     _console.drawGrid(false);
// }

// int Shooting::selectShot()
// {   
//     if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
//         _selectShotPos();
//         Game::changePlayers();
//     }
//     else _autoSelectShotPos();

//     return 0;
// }

// Reactions Shooting::checkReaction(int row, int col)
// {
//     int val = Game::getCurrEnemy()->grid->getSquare(row, col);

//     if (val >= 8 && val % 8 == 0) return Reactions::HIT;
//     else if (val == static_cast<int>(SquareValues::MISS) || (val >= 8 && val % 8 == 0)) return Reactions::AGAIN;
//     else return Reactions::MISS;

//     return Reactions::MISS;
// }

// void Shooting::_selectShotPos()
// {
//     print();

//     string ans = _console.input("To shot: <a-j><1-10>");
//     regex rex{"(([a-j])([1-9]|10))"};
//     smatch matches;

//     int row{}, col{};

//     if (regex_match(ans, matches, rex)) {
//         row = int(tolower(matches[2].str().c_str()[0])) - 97;
//         col = stoi(matches[3].str().c_str()) - 1;
//         int val{Game::getCurrEnemy()->grid->getSquare(row, col)};

//         string rowName{matches[2]};
//         string colName{matches[3]};

//         Ship* ship{Game::getCurrPlayer()->grid->getShipByVal(val)};

//         switch (checkReaction(row, col))
//         {
//         case Reactions::HIT:
//             ship->hit();

//             if (ship->isSink()) {
//                 _sunkShip(ship);
//                 print();
//                 _console.drawInfo("You sunk the ship!");
//             }
//             else {
//                 _hitShip(row, col);
//                 print();
//                 _console.drawInfo("You hit the ship!");
//             }

//             _selectShotPos();
//             break;
//         case Reactions::AGAIN:
//             _askAgain("You cannot shot to square which has already been shoted!");
//             _selectShotPos();
//             break;
//         case Reactions::MISS:
//             Game::getCurrEnemy()->grid->setSquare(row, col, static_cast<int>(SquareValues::MISS));
//             print();
//             _console.drawInfo("You missed!", true);
//             break;
//         default:
//         }
//     }
//     else {
//         _askAgain("Wrong position");
//         _selectShotPos();
//     }
// }

// void Shooting::_autoSelectShotPos(bool isHit)
// {
//     int row{}, col{}, orient{};
//     char rowName{char(97 + row)};

//     // if (isHit) {
//     //     array<int, 4> rowPos{ -1, 0, 1, 0 };
//     //     array<int, 4> colPos{ 0, 1, 0, -1 };

//     //     for (int i{}; i < rowPos.size(); i++) {

//     //     }
//     // }
//     // else {
//     //     row = rand() % 10;
//     //     col = rand() % 10;
//     //     orient = rand() % 2;
//     // }

//     switch (checkReaction(row, col))
//     {
//     case Reactions::HIT:
//         print();
//         _console.drawInfo(format("COMP shoted on {}{}{}{}", Tools::ft["underline"], rowName, col, Tools::ft["endf"]), true);
//         _autoSelectShotPos(true);
//         break;
//     case Reactions::AGAIN:
//         _autoSelectShotPos();
//         break;
//     case Reactions::MISS:
//         Game::getCurrEnemy()->grid->setSquare(row, col, static_cast<int>(SquareValues::MISS));
//         print();
//         _console.drawInfo(format("COMP missed on {}{}{}{}", Tools::ft["underline"], rowName, col, Tools::ft["endf"]), true);
//         break;
//     default:
//     }

//     Game::changePlayers();
// }

// void Shooting::_hitShip(int row, int col)
// {
//     Game::getCurrEnemy()->grid->setSquare(row, col, static_cast<int>(SquareValues::HIT));
// }

// void Shooting::_sunkShip(Ship* ship)
// {
//     int orient = ship->getOrient();
//     auto pos = ship->getPos();
//     cout << pos["row"] << " " << pos["col"] << "\n";

//     for (int i{}; i < ship->getLen(); i++) {
//         Game::getCurrEnemy()->grid->setSquare(
//             (orient == 0 ? pos["row"] : pos["row"] + i),
//             (orient == 0 ? pos["col"] + i : pos["col"]),
//             static_cast<int>(SquareValues::SUNK)
//         );
//     }
// }

// void Shooting::_askAgain(string msg)
// {
//     print();
//     _console.drawError(msg);
// }
