#include "player.h"

void Player::_clear()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) grid[i][j] = squareStates::EMPTY;
    }
}

Player::Player(string name)
{
    _name = name;
    _clear();
}

string Player::getName()
{
    return _name;
}
