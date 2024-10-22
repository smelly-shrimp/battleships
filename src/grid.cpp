#include <array>
#include <sstream>
#include "grid.h"

#define OCCUP -1
#define MISS 1
#define HIT 2
#define SUNK 3

using std::array, std::stringstream;

Grid::Grid()
{
    array<int, 10> vals{ 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    for (int i{}; i < vals.size(); i++) {
        _ships[i] = new Ship(i + 1, vals[i]);
    }
}

int Grid::getSquare(int col, int row)
{
    return _grid[col][row];
}

void Grid::setSquare(int col, int row, int val)
{
    if (col < _grid.size() && col >= 0 && row < _grid.size() && row >= 0) {
        _grid[row][col] = val;
    }
}

bool Grid::isAvailable(int col, int row, int len, int orient)
{
    if (orient == 0 ? col + len > _grid.size() : row + len > _grid.size()) return false;

    for (int i{}; i < len + 2; i++) {
        if (col + i - 1 < _grid.size() && col + i - 1 >= 0
            && row + i - 1 < _grid.size() && row + i - 1 >= 0) {

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
        if (val >= 8 && val % 8 == HIT) ss << "▒▒";
        else if (val == 1) ss << "⋅⋅";
        else ss << "░░";
    }
    else {
        if (val >= 8 && val % 8 == 0) ss << "██";
        // else if (val >= 8 && val) {}
        // else if (val == -1) {
        //     // ss << "••";
        //     ss << "⋅⋅";
        //     // ss << "><";
        // }
        else ss << "══";
        // else ss << "▁▁";
    }

    ss << " ";
    return ss.str();
}

void Grid::setOccup(int col, int row, int len, int orient)
{
    for (int i{}; i < len + 2; i++) {
        orient == 0 ? setSquare(col + i - 1, row - 1, OCCUP) : setSquare(col + 1, row + i - 1, OCCUP);
        orient == 0 ? setSquare(col + i - 1, row + 1, OCCUP) : setSquare(col - 1, row + i - 1, OCCUP);
        if (i <= 0 || i >= len + 1) {
            orient == 0 ? setSquare(col + i - 1, row, OCCUP) : setSquare(col, row + i - 1, OCCUP);
        }
    }
}

Ship* Grid::getCurrShip()
{
    return _currShip;
}

void Grid::setCurrShip(int idx)
{
    _currShip = _ships[idx];
}
