#ifndef GRID_H
#define GRID_H

#include <string>
#include "ship.h"

using namespace std;

class Grid
{
    public:
        Grid();
        void setShip(int x, int y, int rotation, int val, int length);
        string getGrid();
        string getShipList();
    private:
        void _init();
        int _grid[10][10];
        Ship* _ships[10];
};

#endif // !GRID_H
