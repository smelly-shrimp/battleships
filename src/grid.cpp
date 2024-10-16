#include <iostream>
#include <sstream>
#include "grid.h"

using namespace std;

Grid::Grid()
{
    _clear();
}

void Grid::setSquare(int x, int y, int val)
{
    _grid[x][y] = val;
}

string Grid::getGrid()
{
    ostringstream ss;
    ss << "========= OCEAN GRID =========="
        << ". 01 02 03 04 05 06 07 08 09 10" << endl;
    for (int x = 0; x < 10; x++) {
        ss << char(65 + x) << " ";
        for (int y = 0; y < 10; y++) {
            ss << (_grid[x][y] == 0 ? "\2588\2588" : "__" ) << " ";
        }

        ss << endl;
    }
}

void Grid::_clear()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) _grid[i][j] = 0;
    }
}
