#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>
#include "ship.h"

enum GridType
{
    OCEAN,
    TARGET,
};

class Grid
{
    public:
        Grid();
        void setShip(int col, int row, int len, int orient, int val);
        std::string reloadGrid();
        std::string getShipList();
        bool isAvaible(int col, int row, int len, int orient);
        void setSquare(int col, int row, int val);
    private:
        std::string _fillOceanGrid(int i);
        std::string _fillTargetGrid(int i);
        void _init();
        int _grid[10][10];
        std::vector<Ship*> _ships;
        Ship* _currShip;
};

#endif // !GRID_H
