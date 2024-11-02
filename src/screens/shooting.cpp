#include <array>
#include <format>
#include <regex>
#include <string>
#include "shooting.h"
#include "game.h"
#include "tools.h"

using std::array, std::format, std::regex, std::smatch, std::stoi, std::string;

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
    else _autoSelectShotPos(false);

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
        char rowName = tolower(matches[2].str().c_str()[0]);

        ShotPos pos{row, col};

        switch (checkReaction(pos))
        {
        case Reactions::HIT:
            print();
            _console.drawInfo(format("You hit a ship on {}{}{}{}!",
                    Tools::ft["underline"], rowName, col + 1, Tools::ft["endf"]));
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
            _console.drawInfo(format("You missed on {}{}{}{}!",
                    Tools::ft["underline"], rowName, col + 1, Tools::ft["endf"]), true);
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

void Shooting::_autoSelectShotPos(bool isHit, ShotPos hitPos)
{
    int row{}, col{};

    if (isHit) {
        array<int, 4> rowPos{ -1, 0, 1, 0 };
        array<int, 4> colPos{ 0, 1, 0, -1 };

        int val{_stage % 4}; 
        row = hitPos.row + rowPos[val];
        col = hitPos.col + colPos[val];

        _stage++;
    }
    else {
        do {
            row = rand() % 10;
            col = rand() % 10;
        } while (_getMaxChunk() == row / 5 + 2 * (col / 5));
    }
    
    ShotPos pos{row, col};
    switch (checkReaction(pos))
    {
    case Reactions::HIT:
        print();
        _console.drawInfo(format("Comp hit your ship on {}{}{}{}!",
                Tools::ft["underline"], static_cast<char>(row + 97), col + 1, Tools::ft["endf"]));
        _autoSelectShotPos(true, pos);
        break;
    case Reactions::SUNK:
        print();
        _console.drawInfo("Comp sunk your ship!", true);
        _autoSelectShotPos(false);
        break;
    case Reactions::AGAIN:
        _autoSelectShotPos(false);
        break;
    case Reactions::MISS:
        print();
        _console.drawInfo("Comp missed!");
        break;
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

int Shooting::_getMaxChunk()
{
    auto grid{Game::getCurrEnemy()->grid->getGrid()};
    array<int, 4> vals{};

    for (int i{}; i < grid.size(); i++) {
        for (int j{}; j < grid.size(); j++) {
            vals.at(i / 5 + 2 * (j / 5)) = grid[i][j] == 3;
        }
    }

    int maxIdx{};
    for (int i{}; i < vals.size(); i++) {
        if (maxIdx < vals.at(i)) maxIdx = i;
    }

    return maxIdx;
}
