#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "grid.h"

class Player
{
    public:
        Grid grid;
        Player(std::string name);
        std::string getName();
    private:
        std::string _name;
};

class Human : public Player
{
    using Player::Player;
};

class Comp : public Player
{
    using Player::Player;
};

#endif // !PLAYER_H
