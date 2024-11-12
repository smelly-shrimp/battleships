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
        _currShotInfo = Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN ? &_humanShotInfo : &_compShotInfo;

        if (Game::getCurrPlayer()->getType() == PlayerTypes::HUMAN) {
            _selectShotPos();
        }
        else {
            _autoSelectShotPos();
        }

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
    int val{Game::getCurrEnemy()->grid->getSquare(_currShotInfo->row, _currShotInfo->col)};
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
        _humanShotInfo.row = static_cast<int>(tolower(matches[2].str().c_str()[0])) - 97;
        _humanShotInfo.col = stoi(matches[3].str().c_str()) - 1;
    }
    else {
        print();
        _console.drawInfo("Wrong position!", InfoType::ERR);
        return _selectShotPos();
    }
}

void Shooting::_autoSelectShotPos()
{
    int& r{_compShotInfo.row};
    int& c{_compShotInfo.col};

    if (_compShotInfo.hitCount > 0) {
        array<int, 4> dr{ -1, 0, 1, 0 };
        array<int, 4> dc{ 0, 1, 0, -1 };

        int val{Game::getCurrEnemy()->grid->getSquare(r, c)};
        bool isHit{val == 3};

        printf("%d\n", _compShotInfo.hitCount);
        if (_compShotInfo.hitCount == 1 && !isHit) {
            _compShotInfo.hitStage++;
        }
        else if (_compShotInfo.hitCount >= 2 && !isHit) {
            _compShotInfo.hitStage += 2;
            _compShotInfo.prevRow = _compShotInfo.firstRow;
            _compShotInfo.prevCol = _compShotInfo.firstCol;
        }

        _compShotInfo.hitStage = _compShotInfo.hitStage % 4;
        r = _compShotInfo.prevRow + dr[_compShotInfo.hitStage];
        c = _compShotInfo.prevCol + dc[_compShotInfo.hitStage];
    }
    else {
        r = rand() % 10;
        c = rand() % 10;
    }
}

bool Shooting::_shoot()
{   
    int val{Game::getCurrEnemy()->grid->getSquare(_currShotInfo->row, _currShotInfo->col)};
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
        grid->setSquare(_currShotInfo->row, _currShotInfo->col, static_cast<int>(SquareValues::MISS));
        _inform(format("{} missed", prefix), InfoType::WARN);
        return false;
    case Reactions::HIT: // refactor this mess
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

            Game::getCurrEnemy()->grid->setOccup(spos["row"], spos["col"], ship->getLen(), orient, static_cast<int>(SquareValues::OCCUP));
            _inform(format("{} sunk ship", prefix), InfoType::SUCC);
            if (ptype == PlayerTypes::COMP) {
                _currShotInfo->hitCount = 0;
                _currShotInfo->hitStage = 0;
            }
        }
        else {
            grid->setSquare(_currShotInfo->row, _currShotInfo->col, static_cast<int>(SquareValues::HIT));
            _inform(format("{} hit ship", prefix), InfoType::SUCC);
            if (ptype == PlayerTypes::COMP) {
                _currShotInfo->hitCount++;
                _currShotInfo->prevRow = _currShotInfo->row;
                _currShotInfo->prevCol = _currShotInfo->col;
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
        Tools::ft["underline"], static_cast<char>(_currShotInfo->row + 97), _currShotInfo->col + 1, Tools::ft["endf"]), type);
}
