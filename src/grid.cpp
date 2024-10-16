#include <iostream>
#include <sstream>
#include <iomanip>
#include <ios>
#include "grid.h"

using namespace std;

Grid::Grid()
{
    _clear();
}

void Grid::setShip(int x, int y, int rotation, int val, int length)
{
    for (int i = 0; i < length; i++) {
        cout << rotation << endl;
        rotation == 0 ? _grid[x + i][y] = val : _grid[x][y + i] = val;
    }
}

string Grid::getGrid()
{
    ostringstream ss;
    ss << "========= OCEAN GRID ==========" << endl
        << ". 01 02 03 04 05 06 07 08 09 10" << endl;
        
    for (int y = 0; y < 10; y++) {
        ss << char(65 + y) << " ";
        for (int x = 0; x < 10; x++) {
            ss << (_grid[x][y] == 0 ? "__" : "\u2588\u2588" ) << " ";
        }

        ss << endl;
    }
    
    return ss.str();
}

string Grid::getShipList()
{
    ostringstream ss;
    string names[4] = { "single-masted", "two-masted   ", "three-masted ", "four-masted  " };
    int size = sizeof(names) / sizeof(names[0]);
    ss << "\n\n";
    for (int i = 0; i < size; i++) {
        ss << names[i];
        for (int j = 0; j <= i; j++) ss << " __";
        ss << endl;
    }

    ss << "\n";

    return ss.str();
}

void Grid::_clear()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) _grid[i][j] = 0;
    }
}
