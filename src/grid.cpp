#include <array>
#include <map>
#include <sstream>
#include "grid.h"
#include "game.h"

using std::array, std::map, std::stringstream, std::string;

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
    if (row < _grid.size() && row >= 0 && col < _grid.size() && col >= 0) {
        _grid[row][col] = val;
    }
}

bool Grid::isAvailable(int row, int col, int len, int orient)
{
    if (orient == 0 ? col + len > _grid.size() : row + len > _grid.size()) return false;

    for (int i{}; i < len + 2; i++) {
        for (int j{}; j < 3; j++) {
            int r{orient == 0 ? row + j - 1 : row + i - 1};
            int c{orient == 0 ? col + i - 1 : col + j - 1};
            if (!_getVal(r, c)) return false;
        }
    }

    return true;
}

bool Grid::_getVal(int row, int col)
{
    if (row >= 0 && row < 10 && col >= 0 && col < 10) {
        const int val{_grid[row][col]};
        return !(val != 0 && val != static_cast<int>(SquareValues::OCCUP));
    }
    else return true;
}

array<Ship*, 10> Grid::getShipList()
{
    return _ships;
}

array<array<int, 10>, 10> Grid::getGrid()
{
    return _grid;
}

string Grid::asString(int val, bool isTarget)
{
    stringstream ss;

    if (isTarget) {
        if (val == static_cast<int>(SquareValues::HIT)) ss << "❯❮";
        else if (val == static_cast<int>(SquareValues::SUNK)) ss << "██";
        else if (val == static_cast<int>(SquareValues::OCCUP)) ss << "××";
        else if (val == static_cast<int>(SquareValues::MISS)) ss << "••";
        else ss << "══";
    }
    else {
        if (val >= 8 && val % 8 == 0) ss << "██";
        else if (val == static_cast<int>(SquareValues::HIT) || val == static_cast<int>(SquareValues::SUNK)) ss << "❯❮";
        else if (val == static_cast<int>(SquareValues::OCCUP)) ss << "××";
        else if (val == static_cast<int>(SquareValues::MISS)) ss << "••";
        else ss << "══";
    }

    ss << " ";
    return ss.str();
}

void Grid::setOccup(int row, int col, int len, int orient, int val)
{
    for (int i{}; i < len + 2; i++) {
        for (int j{}; j < 3; j++) {
            int r{orient == 0 ? row - 1 + j : row - 1 + i};
            int c{orient == 0 ? col - 1 + i : col - 1 + j};
            if (getSquare(r, c) == 0) setSquare(r, c, val);
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
