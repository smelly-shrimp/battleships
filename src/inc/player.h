#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "grid.h"

enum PlayerTypes
{
    HUMAN,
    COMP,
};

class Player
{
    public:
        Grid grid;
        Player(std::string name, PlayerTypes type);
        PlayerTypes getType();
        std::string getName();
    private:
        PlayerTypes _type;
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
