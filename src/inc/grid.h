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
        int getSquare(int col, int row);
        void setSquare(int col, int row, int val);
        bool isAvailable(int col, int row, int len, int orient);
        std::array<Ship*, 10> getShipList();
        std::array<std::array<int, 10>, 10> getGrid();
        std::string asString(int val, bool isTarget = false);
        Ship* getCurrShip();
        void setCurrShip(int idx);
        void setOccup(int row, int col, int len, int orient, int val);
        Ship* getShipByVal(int val);
    private:
        std::array<std::array<int, 10>, 10> _grid{0};
        std::array<Ship*, 10> _ships{};
        Ship* _currShip{};
        bool _getVal(int row, int col);
};

#endif // !GRID_H
