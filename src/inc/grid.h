#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>
#include "ship.h"

class Grid
{
    public:
        Grid();
        void setShip(int col, int row, int len, int orient, int val);
        std::string getGrid();
        std::string getShipList();
        bool isAvaible(int col, int row, int len, int orient);
    private:
        void _init();
        int _grid[10][10];
        std::vector<Ship*> _ships;
        Ship* _currShip;
        int _getSquare(int col, int row);
        void _setSquare(int col, int row, int val);
};

#endif // !GRID_H
