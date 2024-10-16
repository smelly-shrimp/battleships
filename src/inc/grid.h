#ifndef GRID_H
#define GRID_H

#include <map>

class Grid
{
    public:
        Grid();
        void setSquare(int x, int y, int val);
        std::string getGrid();
    private:
        void _clear();
        int _grid[10][10];
        std::map<int, int> _ships = { { 4, 1 }, { 3, 2 }, { 2, 3 }, { 1, 4 } };
};

#endif // !GRID_H
