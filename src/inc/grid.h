#ifndef GRID_H
#define GRID_H

#include <string>
using namespace std;

class Grid
{
    public:
        Grid();
        void setShip(int x, int y, int rotation, int val, int length);
        string getGrid();
        string getShipList();
    private:
        void _clear();
        int _grid[10][10];
};

#endif // !GRID_H
