#include <iostream>
#include <array>
#include <sstream>
#include "grid.h"
#include "ship.h"
#include "game.h"
#include "tools.h"

using std::cout, std::string, std::ostringstream, std::array;

// #define FORBIDDEN -13;
// #define OCCUP -1
// #define EMPTY 0
// #define SHIP 1
// #define HIT 2
// #define MISS -2
// #define OWN_HIT 3

// #define FORBIDDEN -13
// #define EMPTY 0
#define OCCUP -1
#define SHIP 1
#define HIT 2
#define MISS 3

Grid::Grid()
{
    _init();
}

void Grid::createShip(int col, int row, int len, int orient, int val)
{
    _useShip(len);
    _setShip(col, row, len, orient);
    _setOccup(col, row, len, orient);
}

string Grid::reload()
{
    ostringstream ss;

    switch(Game::getGameState())
    {
    case ARRANGE:
        ss << Tools::insertChars(" ", 8) << "========= OCEAN GRID ==========\n"
        << "        . 01 02 03 04 05 06 07 08 09 10\n";
            
        for (int i = 0; i < _grid.size(); i++) {
            ss << "        " << char(65 + i) << " ";
            ss << _asString(i);
            ss << "\n";
        }

        ss << "\n";

        break;

    case SHOOTING:
        ss << Tools::insertChars(" ", 8) << "========= OCEAN GRID ==========>|<======== TARGET GRID =========\n"
           << Tools::insertChars(" ", 8) << ". 01 02 03 04 05 06 07 08 09 10  . 01 02 03 04 05 06 07 08 09 10\n";

        for (int i = 0; i < _grid.size(); i++) {
            ss << Tools::insertChars(" ", 8) << char(65 + i) << " ";
            ss << _asString(i, GridType::OCEAN);
            ss << " " << char(65 + i) << " ";
            ss << _asString(i, GridType::TARGET);
            ss << "\n";
        }

        ss << "\n";

        break;
    default:
        cout << "Unkown type!\n";
    }
        
    return ss.str();
}

string Grid::getShipList()
{
    ostringstream ss;
    array<string, 4> names{ "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    int curr = 0;
    for (int i = 0; i < 4; i++) {
        ss << Tools::insertChars(" ", 8) << names.at(i);
        for (int j = 0; j <= i && curr < _ships.size(); j++) {
            ss << (_ships.at(curr)->isUsed() ? " ██" : " ░░");
            curr += 1;
        }
        ss << "\n";
    }

    ss << "\n";

    return ss.str();
}

bool Grid::isAvaible(int col, int row, int len, int orient)
{
    if (orient == 0 ? col + len > _grid.size() : row + len > _grid.size()) return false;

    for (int i = 0; i < len + 2; i++) {
        if (col + i - 1 < _grid.size() && col + i - 1 >= 0
            && row + i - 1 < _grid.size() && row + i - 1 >= 0) {
            for(int j = 0; j < 3; j++) {
                int val = orient == 0 ?
                    _grid[row + j - 1][col + i - 1]
                    : _grid[row + i - 1][col + j - 1];

                if (val == 1) return false;
            }
        }
    }

    return true;
}

void Grid::setSquare(int col, int row, int val)
{
    if (col < _grid.size() && col >= 0 && row < _grid.size() && row >= 0) {
        _grid[row][col] = val;
    }
}

int Grid::getSquare(int col, int row)
{
    return _grid[row][col];
}

void Grid::_init()
{
    array<int, 10> vals{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    for (int i = 0; i < vals.size(); i++) {
        _ships.push_back(new Ship(vals[i]));
    }
}

void Grid::_useShip(int len)
{
    for (int i = 0; i < _ships.size(); i++) {
        if (_ships.at(i)->getLength() == len && !_ships.at(i)->isUsed()) {
            _ships.at(i)->use();
            break;
        }
    }
}

void Grid::_setShip(int col, int row, int len, int orient)
{
    for (int i = 0; i < len; i++) {
        orient == 0 ? setSquare(col + i, row, SHIP) : setSquare(col, row + i, SHIP);
    }
}

void Grid::_setOccup(int col, int row, int len, int orient)
{
    for (int i = 0; i < len + 2; i++) {
        orient == 0 ? setSquare(col + i - 1, row - 1, OCCUP) : setSquare(col + 1, row + i - 1, OCCUP);
        orient == 0 ? setSquare(col + i - 1, row + 1, OCCUP) : setSquare(col - 1, row + i - 1, OCCUP);
        if (i <= 0 || i >= len + 1) {
            orient == 0 ? setSquare(col + i - 1, row, OCCUP) : setSquare(col, row + i - 1, OCCUP);
        }
    }
}

string Grid::_asString(int i, GridType type)
{
    ostringstream ss;

    for (int j = 0; j < _grid.size(); j++) {
        if (type == GridType::OCEAN) {
            switch (_grid[i][j])
            {
            case SHIP:
                ss << "██ ";
                break;
            case OCCUP:
                ss << "·· ";
                break;
            // case OWN_HIT:
            //     ss << "»« ";
            default:
                ss << "░░ ";
            }
        }
        else {
            switch (_grid[i][j])
            {
            case HIT:
                ss << "██ ";
                break;
            case MISS:
                ss << "▂▂ ";
                break;
            default:
                ss << "░░ ";
            }
        }
    }

    return ss.str();
}
