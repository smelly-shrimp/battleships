#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>
#include "ship.h"

class Grid
{
    public:
        Grid();
        void setShip(int x, int y, int len, int orient, int val);
        std::string getGrid();
        std::string getShipList();
        bool isAvaible(int i, int j, int len, int orient);
    private:
        void _init();
        int _grid[10][10];
        std::vector<Ship*> _ships;
        Ship* _currShip;
        void _fillOccup();
};

#endif // !GRID_H
