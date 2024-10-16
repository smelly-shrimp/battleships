#ifndef GRID_H
#define GRID_H

#include <map>
using namespace std;

class Grid
{
    public:
        Grid();
        void setShip(int x, int y, int rotation, int val, int length);
        string getGrid();
        string getShipList();
        map<int, int> ships = { { 4, 1 }, { 3, 2 }, { 2, 3 }, { 1, 4 } };
    private:
        void _clear();
        int _grid[10][10];
};

#endif // !GRID_H
