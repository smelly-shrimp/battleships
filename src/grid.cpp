#include "grid.h"

Grid::Grid()
{
    _clear();
}

void Grid::_clear()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) grid[i][j] = 0;
    }
}
