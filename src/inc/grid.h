#ifndef GRID_H
#define GRID_H

#include <string>
#include <array>
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
        void createShip(int col, int row, int len, int orient, int val);
        std::string reload();
        std::string getShipList();
        bool isAvaible(int col, int row, int len, int orient);
        void setSquare(int col, int row, int val);
        int getSquare(int col, int row);
    private:
        void _init();
        void _useShip(int len);
        void _setShip(int col, int row, int len, int orient);
        void _setOccup(int col, int row, int len, int orient);
        std::string _asString(int i, GridType type = OCEAN);
        std::array<std::array<int, 10>, 10> _grid{0};

        std::vector<Ship*> _ships;
};

#endif // !GRID_H
