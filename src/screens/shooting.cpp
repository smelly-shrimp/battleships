#include <array>
#include <format>
#include <regex>
#include <string>
#include "shooting.h"
#include "game.h"
#include "tools.h"

#include <iostream>

using std::array, std::format, std::regex, std::smatch, std::stoi, std::string;

void Shooting::print()
{
    _console.drawShipList(false, Game::getCurrPlayer()->getType() == PlayerTypes::COMP);
    _console.drawGrid(false, Game::getCurrPlayer()->getType() == PlayerTypes::COMP);
}

void Shooting::update()
{
    while (!_isEnd()) {
        if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
            _selectShotPos();
        }
        else _autoSelectShotPos();

        if (!_shoot()) {
            if (Game::isHvsH()) _console.cover();
            Game::changePlayers();
        }
    }
}

bool Shooting::_isEnd()
{
    int cnt{};
    for (Ship* ship : Game::getCurrEnemy()->grid->getShipList()) {
        if (ship->isSunk()) cnt++;
    }

    if (cnt >= 10) {
        Game::addPoint(Game::getCurrPlayer());
        return true;
    }
    
    return false;
}

Reactions Shooting::_checkReaction()
{
    int val{Game::getCurrEnemy()->grid->getSquare(_shotInfo.row, _shotInfo.col)};
    Ship* ship{Game::getCurrEnemy()->grid->getShipByVal(val)};

    if (val >= 8 && val % 8 == 0) return Reactions::HIT;
    else if (val == static_cast<int>(SquareValues::MISS)
          || val == static_cast<int>(SquareValues::HIT)
          || val == static_cast<int>(SquareValues::SUNK)
          || val == static_cast<int>(SquareValues::OCCUP)) {
        return Reactions::AGAIN;
    }
    else return Reactions::MISS;
}

void Shooting::_selectShotPos()
{
    print();
    string ans = _console.input("To shot: <a-j><1-10>");

    regex re{"(([a-j])([1-9]|10))"};
    smatch matches;

    if (regex_match(ans, matches, re)) {
        _shotInfo.row = static_cast<int>(tolower(matches[2].str().c_str()[0])) - 97;
        _shotInfo.col = stoi(matches[3].str().c_str()) - 1;
    }
    else {
        print();
        _console.drawInfo("Wrong position!", InfoType::ERR);
        _selectShotPos();
    }
}

void Shooting::_autoSelectShotPos()
{
    if (_shotInfo.hitCount > 0) {
        array<int, 4> rowPos{ -1, 0, 1, 0 };
        array<int, 4> colPos{ 0, 1, 0, -1 };

        int& r{_shotInfo.row};
        int& c{_shotInfo.col};

        int dir{_shotInfo.hitStage % 4}; // add random

        r = _shotInfo.prevRow + rowPos[_shotInfo.hitCount > 1 ? _shotInfo.dir : dir];
        c = _shotInfo.prevCol + colPos[_shotInfo.hitCount > 1 ? _shotInfo.dir : dir];
        
        if (r < 0 || r > 9 || c < 0 || c > 9) return _autoSelectShotPos();

        int val{Game::getCurrEnemy()->grid->getSquare(r, c)};
        bool isHit{val >= 8 && val % 8 == 0};

        if (_shotInfo.hitCount >= 1 && isHit) _shotInfo.dir = dir;

        if (!isHit) _shotInfo.dir *= -1;

        _shotInfo.hitStage++;
    }
    else {
        do {
            _shotInfo.row = rand() % 10;
            _shotInfo.col = rand() % 10;
            _shotInfo.firstRow = _shotInfo.row;
            _shotInfo.firstCol = _shotInfo.col;
        } while (_getMaxChunk() == _shotInfo.row / 5 + 2 * (_shotInfo.col / 5));    
    }
}

bool Shooting::_shoot()
{
    int val{Game::getCurrEnemy()->grid->getSquare(_shotInfo.row, _shotInfo.col)};
    Grid* grid{Game::getCurrEnemy()->grid};
    Ship* ship{Game::getCurrEnemy()->grid->getShipByVal(val)};

    PlayerTypes ptype{Game::getCurrPlayer()->getType()};
    string prefix{ptype == PlayerTypes::HUMAN ? "You've" : "Comp"};

    switch (_checkReaction())
    {
    case Reactions::AGAIN:
        if (ptype == PlayerTypes::HUMAN) _inform("You cannot shoot again", InfoType::ERR);
        return true;
    case Reactions::MISS:
        grid->setSquare(_shotInfo.row, _shotInfo.col, static_cast<int>(SquareValues::MISS));
        _inform(format("{} missed", prefix), InfoType::WARN);
        return false;
    case Reactions::HIT: // todo: refactor this mess
        ship->hit();
        if (ship->isSunk()) {
            auto spos{ship->getPos()};
            int orient{ship->getOrient()};

            for (int i{}; i < ship->getLen(); i++) {
                grid->setSquare(
                    (orient == 0 ? spos["row"] : spos["row"] + i),
                    (orient == 0 ? spos["col"] + i : spos["col"]),
                    static_cast<int>(SquareValues::SUNK));
            }

            Game::getCurrEnemy()->grid->setOccup(spos["row"], spos["col"], ship->getLen(), orient, -1);
            _inform(format("{} sunk ship", prefix), InfoType::SUCC);
            if (ptype == PlayerTypes::COMP) _shotInfo.hitCount = 0;
        }
        else {
            grid->setSquare(_shotInfo.row, _shotInfo.col, static_cast<int>(SquareValues::HIT));
            _inform(format("{} hit ship", prefix), InfoType::SUCC);
            if (ptype == PlayerTypes::COMP) {
                _shotInfo.prevRow = _shotInfo.row;
                _shotInfo.prevCol = _shotInfo.col;
                _shotInfo.hitCount += 1;
                _shotInfo.hitStage = 0;
            }
        }
        return true;
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

void Shooting::_inform(string msg, InfoType type)
{
    print();
    _console.drawInfo(format("{} on {}{}{}{}!", msg,
        Tools::ft["underline"], static_cast<char>(_shotInfo.row + 97), _shotInfo.col + 1, Tools::ft["endf"]), type);
}
