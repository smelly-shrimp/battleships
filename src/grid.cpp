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

void Grid::setShip(int x, int y, int rotation, int val, int length)
{
    for (int i = 0; i < _ships.size(); i++) {
        if (_ships.at(i)->getLength() == length && !_ships.at(i)->isUsed()) {
            _ships.at(i)->use();
            break;
        }
    }

    for (int i = 0; i < length; i++) {
        rotation == 0 ? _grid[x + i][y] = val : _grid[x][y + i] = val;
    }
}

string Grid::getGrid()
{
    ostringstream ss;
    ss << "========= OCEAN GRID ==========" << endl
       << ". 01 02 03 04 05 06 07 08 09 10" << endl;
        
    for (int y = 0; y < _ships.size(); y++) {
        ss << char(65 + y) << " ";

        for (int x = 0; x < _ships.size(); x++) {
            ss << (_grid[x][y] == 0 ? "__" : "\u2588\u2588" ) << " ";
        }

        ss << endl;
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
        ss << names[i];
        for (int j = 0; j <= i && curr < _ships.size(); j++) {
            ss << (_ships.at(curr)->isUsed() ? " \u2588\u2588" : " __");
            curr += 1;
        }

        ss << endl;
    }

    ss << endl;

    return ss.str();
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
