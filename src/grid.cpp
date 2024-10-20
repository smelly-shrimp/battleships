#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ios>
#include "grid.h"
#include "ship.h"
#include "game.h"

using namespace std;

#define FORBIDDEN -13;
#define OCCUP -1
#define EMPTY 0
#define SHIP 1
#define HIT 2;

Grid::Grid()
{
    _init();
}

void Grid::setShip(int col, int row, int len, int orient, int val)
{
    for (int i = 0; i < _ships.size(); i++) {
        if (_ships.at(i)->getLength() == len && !_ships.at(i)->isUsed()) {
            _ships.at(i)->use();
            _currShip = _ships.at(i);
            break;
        }
    }

    for (int i = 0; i < len; i++) {
        orient == 0 ? setSquare(col + i, row, SHIP) : setSquare(col, row + i, SHIP);
    }

    for (int i = 0; i < len + 2; i++) {
        orient == 0 ? setSquare(col + i - 1, row - 1, OCCUP) : setSquare(col + 1, row + i - 1, OCCUP);
        orient == 0 ? setSquare(col + i - 1, row + 1, OCCUP) : setSquare(col - 1, row + i - 1, OCCUP);
        if (i <= 0 || i >= len + 1) {
            orient == 0 ? setSquare(col + i - 1, row, OCCUP) : setSquare(col, row + i - 1, OCCUP);
        }
    }
}

string Grid::reloadGrid()
{
    ostringstream ss;

    switch(Game::getGameState())
    {
    case ARRANGE:
        ss << "        ========= OCEAN GRID ==========\n"
        << "        . 01 02 03 04 05 06 07 08 09 10\n";
            
        for (int i = 0; i < 10; i++) {
            ss << "        " << char(65 + i) << " ";
            ss << _fillOceanGrid(i);
            ss << "\n";
        }

        ss << "\n";

        break;

    case SHOOTING:
        ss << "       ========= OCEAN GRID ==========>|<======== TARGET GRID =========\n"
        <<    "       . 01 02 03 04 05 06 07 08 09 10  . 01 02 03 04 05 06 07 08 09 10\n";

        for (int i = 0; i < 10; i++) {
            ss << "       " << char(65 + i) << " ";
            ss << _fillTargetGrid(i);
            ss << " " << char(65 + i) << " ";
            ss << _fillTargetGrid(i);
            ss << "\n";
        }

        ss << "\n";

        break;
    default:
        printf("Unkown type!\n");
    }
        
    return ss.str();
}

string Grid::getShipList()
{
    ostringstream ss;
    string names[4] = { "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    ss << "\n\n";

    int curr = 0;
    for (int i = 0; i < 4; i++) {
        ss << "        " << names[i];
        for (int j = 0; j <= i && curr < _ships.size(); j++) {
            ss << (_ships.at(curr)->isUsed() ? " ██" : " ░░");
            curr += 1;
        }
        ss << "\n";
    }

    ss << "\n";

    return ss.str();
}

string Grid::_fillOceanGrid(int i)
{
    ostringstream ss;

    for (int j = 0; j < 10; j++) {
        switch (_grid[i][j])
        {
        case SHIP:
            ss << "██ ";
            break;
        case OCCUP:
            ss << ">< ";
            break;
        default:
            ss << "░░ ";
            break;
        }
    }

    return ss.str();
}

std::string Grid::_fillTargetGrid(int i)
{
    ostringstream ss;

    for (int j = 0; j < 10; j++) {
        switch (_grid[i][j])
        {
        case SHIP:
            ss << "██ ";
            break;
        case OCCUP:
            ss << ">< ";
            break;
        default:
            ss << "░░ ";
            break;
        }
    }

    return ss.str();
}

bool Grid::isAvaible(int col, int row, int len, int orient)
{
    if (orient == 0 ? col + len > 10 : row + len > 10) return false;

    for (int k = 0; k < len + 2; k++) {
        for (int l = 0; l < 3; l++) {
            int val = orient == 0 ?
                _grid[row + l - 1][col + k - 1]
                : _grid[row + k - 1][col + l - 1];
            if (val == 1) return false;
        }
    }

    return true;
}

void Grid::_init()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) _grid[i][j] = 0;
    }

    int vals[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for (int i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        _ships.push_back(new Ship(vals[i]));
    }
}

void Grid::setSquare(int col, int row, int val)
{
    if (col < 10 && col >= 0 && row < 10 && row >= 0) {
        _grid[row][col] = val;
    }
}
