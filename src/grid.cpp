#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ios>
#include "grid.h"
#include "ship.h"

using namespace std;

Grid::Grid()
{
    _init();
}

void Grid::setShip(int x, int y, int len, int rot, int val)
{
    for (int i = 0; i < _ships.size(); i++) {
        if (_ships.at(i)->getLength() == len && !_ships.at(i)->isUsed()) {
            _ships.at(i)->use();
            _currShip = _ships.at(i);
            break;
        }
    }

    for (int i = 0; i < len; i++) {
        rot == 0 ? _grid[y][x + i] = val : _grid[y + i][x] = val;
    }

    _fillOccup();
}

string Grid::getGrid()
{
    ostringstream ss;
    ss << "========= OCEAN GRID ==========" << endl
       << ". 01 02 03 04 05 06 07 08 09 10" << endl;
        
    for (int i = 0; i < _ships.size(); i++) {
        ss << char(65 + i) << " ";

        for (int j = 0; j < _ships.size(); j++) {
            switch (_grid[i][j])
            {
            case 1:
                ss << "██" << " ";
                break;
            case -1:
                ss << "><" << " ";
                break;
            default:
                ss << "░░" << " ";
                break;
            }
        }

        ss << endl;
    }
    
    return ss.str();
}

string Grid::getShipList()
{
    ostringstream ss;
    string names[4] = { "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    ss << endl << endl;

    int curr = 0;
    for (int i = 0; i < 4; i++) {
        ss << names[i];
        for (int j = 0; j <= i && curr < _ships.size(); j++) {
            ss << (_ships.at(curr)->isUsed() ? " ██" : " ░░");
            curr += 1;
        }

        ss << endl;
    }

    ss << endl;

    return ss.str();
}

bool Grid::isAvaible(int i, int j, int len, int orient)
{
    printf("%d %d %d %d", i + len, j + len, len, orient);
    if (orient == 0 ? i + len > 10 : j + len > 10) return false;

    for (int k = 0; k < len + 2; k++) {
        for (int l = 0; l < 3; l++) {
            int val = orient == 0 ?
                _grid[j + l - 1][i + k - 1]
                : _grid[i + k - 1][j + l - 1];
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

void Grid::_fillOccup()
{
    int posI[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
    int posJ[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 8; k++) {
                if (_grid[i][j] == 1 && _grid[i + posI[k]][j + posJ[k]] == 0) {
                    _grid[i + posI[k]][j + posJ[k]] = -1;
                }
            }
        }
    }
}
