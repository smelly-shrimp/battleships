#include <array>
#include <map>
#include <sstream>
#include "grid.h"

#define OCCUP -1
#define EMPTY 0
#define SHIP 1
#define MISS 2
#define HIT 3
#define SUNK 4

using std::array, std::map, std::stringstream;

Grid::Grid()
{
    array<int, 10> vals{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    for (int i{}; i < vals.size(); i++) {
        _ships[i] = new Ship(i + 1, vals[i]);
    }
}

int Grid::getSquare(int row, int col)
{
    return _grid[row][col];
}

void Grid::setSquare(int row, int col, int val)
{
    if (row < _grid.size() && row >= 0 && col < _grid.size() && col >= 0 ) {
        _grid[row][col] = val;
    }
}

bool Grid::isAvailable(int row, int col, int len, int orient)
{
    if (orient == 0 ? row + len > _grid.size() : col + len > _grid.size() ) return false;

    for (int i{}; i < len + 2; i++) {
        if (row + i - 1 < _grid.size() && row + i - 1 >= 0
            && col + i - 1 < _grid.size() && col + i - 1 >= 0) {
            for (int j{}; j < 3; j++) {
                int val = orient == 0
                    ? _grid[row + j - 1][col + i - 1]
                    : _grid[row + i - 1][col + j - 1];
                
                if (val >= 8 && val % 8 == 0) return false;
            }
        }
    }

    return true;
}

array<Ship*, 10> Grid::getShipList()
{
    return _ships;
}

std::array<std::array<int, 10>, 10> Grid::getGrid()
{
    return _grid;
}

std::string Grid::asString(int val, bool isTarget)
{
    stringstream ss;

    if (isTarget) {
        if (val == HIT) ss << "❯❮";
        else if (val == SUNK) ss << "██";
        else if (val == MISS) ss << "••";
        else ss << "══";
    }
    else {
        if (val >= 8 && val % 8 == 0) ss << "██";
        else if (val == OCCUP) ss << "••";
        else if (val == HIT || val == SUNK) ss << "❯❮";
        else ss << "══";
    }

    ss << " ";
    return ss.str();
}

void Grid::setOccup(int row, int col, int len, int orient)
{
    for (int i{}; i < len + 2; i++) {
        orient == 0 ? setSquare(row - 1, col + i - 1, OCCUP) : setSquare(row + i - 1, col + 1, OCCUP);
        orient == 0 ? setSquare(row + 1, col + i - 1, OCCUP) : setSquare(row + i - 1, col - 1, OCCUP);
        if (i <= 0 || i >= len + 1) {
            orient == 0 ? setSquare(row, col + i - 1, OCCUP) : setSquare(row + i - 1, col, OCCUP);
        }
    }
}

Ship *Grid::getShipByVal(int val)
{
    for (Ship* ship : _ships) {
        if (ship->getId() == val) return ship;
    }

    return 0;
}

Ship* Grid::getCurrShip()
{
    return _currShip;
}

void Grid::setCurrShip(int idx)
{
    _currShip = _ships[idx];
}
