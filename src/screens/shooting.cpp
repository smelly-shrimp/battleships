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
    if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
        _selectShotPos();
        if (Game::getCurrEnemy()->getType() == PlayerTypes::HUMAN) {
            _console.drawShipList("", true, true);
            _console.drawGrid(false, false, true);
            _console.drawInfo("...");
        }
    }
    else _autoSelectShotPos();

    int cnt{};
    for (Ship* ship : Game::getCurrEnemy()->grid->getShipList()) {
        if (ship->isSink()) cnt++;
    }

    if (cnt >= 9) return 1;

    Game::changePlayers();

    return 0;
}

void Shooting::_selectShotPos()
{
    print();
    string ans = _console.input("To shot: <a-j><1-10>");

    regex re{"(([a-j])([1-9]|10))"};
    smatch matches;
    int row{}, col{};

    if (regex_match(ans, matches, re)) {
        row = static_cast<int>(tolower(matches[2].str().c_str()[0])) - 97;
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
