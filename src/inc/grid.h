#ifndef GRID_H
#define GRID_H

#include <string>
#include <array>
#include <vector>
#include "ship.h"

enum class GridType
{
    OCEAN,
    TARGET,
};

class Grid
{
    public:
        Grid();
        // void createShip(int col, int row, int len, int orient, int val);
        // std::string reload();
        // std::string getShipList();
        // bool isAvaible(int col, int row, int len, int orient);
        int getSquare(int col, int row);
        void setSquare(int col, int row, int val);
        std::array<Ship*, 10> getShipList();
        std::array<std::array<int, 10>, 10> getGrid();
        std::string asString(int val);
    private:
        // void _init();
        // void _useShip(int len);
        // void _sinkShip();
        // void _setShip(int col, int row, int len, int orient);
        // void _setOccup(int col, int row, int len, int orient);
        // std::string _asString(int i, GridType type = OCEAN);
        std::array<std::array<int, 10>, 10> _grid{0};
        std::array<Ship*, 10> _ships;
};

#endif // !GRID_H
