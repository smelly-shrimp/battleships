#include <array>
#include <format>
#include <regex>
#include <string>
#include "shooting.h"
#include "game.h"
#include "tools.h"

#include <iostream>

using std::array, std::format, std::regex, std::smatch, std::stoi, std::string;

// Shooting::Shooting()
// {
//     srand(time(0));
// }

void Shooting::print()
{
    _console.drawShipList(false);
    _console.drawGrid(false, Game::getCurrPlayer()->getType() == PlayerTypes::COMP);
}

void Shooting::update()
{
    while (!isEnd()) {
        ShotPos pos{};
        if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
            pos = _selectShotPos();
        }
        else pos = _autoSelectShotPos();

        // std::cout << pos.row << " " << pos.col << '\n';
        _shoot(pos);

        // if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN
        //  && Game::getCurrEnemy()->getType() == PlayerTypes::HUMAN) {
        //     _console.cover();
        // }

        Game::changePlayers();
    }
}

bool Shooting::isEnd()
{
    int cnt{};
    for (Ship* ship : Game::getCurrEnemy()->grid->getShipList()) {
        if (ship->isSink()) cnt++;
    }

    if (cnt >= 9) return true;
    return false;
}

Reactions Shooting::_checkReaction(ShotPos pos)
{
    int val{Game::getCurrEnemy()->grid->getSquare(pos.row, pos.col)};
    Ship* ship{Game::getCurrEnemy()->grid->getShipByVal(val)};

    if (val >= 8 && val % 8 == 0) {
        return ship->isSink() ? Reactions::SUNK : Reactions::HIT;
    }
    else if (val == static_cast<int>(SquareValues::MISS)
          || val == static_cast<int>(SquareValues::HIT)
          || val == static_cast<int>(SquareValues::SUNK)) {
        return Reactions::AGAIN;
    }
    else return Reactions::MISS;
}

ShotPos Shooting::_selectShotPos()
{
    print();
    string ans = _console.input("To shot: <a-j><1-10>");

    regex re{"(([a-j])([1-9]|10))"};
    smatch matches;

    if (regex_match(ans, matches, re)) {
        int row{static_cast<int>(tolower(matches[2].str().c_str()[0])) - 97};
        int col{stoi(matches[3].str().c_str()) - 1};

        return {row, col};
    }
    else {
        print();
        _console.drawInfo("Wrong position!", InfoType::ERR);
        return _selectShotPos();
    }
}

ShotPos Shooting::_autoSelectShotPos()
{
    int row{}, col{};

    if (_isHit) {
        array<int, 4> rowPos{ -1, 0, 1, 0 };
        array<int, 4> colPos{ 0, 1, 0, -1 };

        int val{_stage % 4};
        row = _hitPos.row + rowPos[val];
        col = _hitPos.col + colPos[val];

        _stage++;    
    }
    else {
        do {
            row = rand() % 10;
            col = rand() % 10;
        } while (_getMaxChunk() == row / 5 + 2 * (col / 5));    
    }

    return {row, col};
}

void Shooting::_shoot(ShotPos pos)
{
    int val{Game::getCurrEnemy()->grid->getSquare(pos.row, pos.col)};
    Grid* grid{Game::getCurrEnemy()->grid};
    Ship* ship{Game::getCurrEnemy()->grid->getShipByVal(val)};

    PlayerTypes ptype{Game::getCurrPlayer()->getType()};
    string prefix{ptype == PlayerTypes::HUMAN ? "You've" : "Comp"};

    switch (_checkReaction(pos))
    {
    case Reactions::AGAIN:
        if (ptype == PlayerTypes::HUMAN) _inform(pos, "You cannot shoot again", InfoType::ERR);
        return _shoot(pos);
    case Reactions::MISS:
        grid->setSquare(pos.row, pos.col, static_cast<int>(SquareValues::MISS));
        _inform(pos, format("{} missed", prefix), InfoType::WARN);
        break;
    case Reactions::SUNK:
        {
        auto spos{ship->getPos()};
        int orient{ship->getOrient()};
        for (int i{}; i < ship->getLen(); i++) {
            grid->setSquare(
                (orient == 0 ? spos["row"] : spos["row"] + i),
                (orient == 0 ? spos["col"] + i : spos["col"]),
                static_cast<int>(SquareValues::SUNK));
        }
        Game::getCurrEnemy()->grid->setOccup(spos["row"], spos["col"], ship->getLen(), orient, -2);
        _inform(pos, format("{} sunk", prefix), InfoType::SUCC);
        if (ptype == PlayerTypes::COMP) _isHit = false;
        return _shoot(pos);
        }
    case Reactions::HIT:
        grid->setSquare(pos.row, pos.col, static_cast<int>(SquareValues::HIT));
        _inform(pos, format("{} hit", prefix), InfoType::SUCC);
        if (ptype == PlayerTypes::COMP) _isHit = true;
        return _shoot(pos);
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

void Shooting::_inform(ShotPos pos, string msg, InfoType type)
{
    print();
    _console.drawInfo(format("{} on {}{}{}{}!", msg,
        Tools::ft["underline"], static_cast<char>(pos.row + 97), pos.col + 1, Tools::ft["endf"]), type);
}
