#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "grid.h"

enum class PlayerTypes
{
    HUMAN,
    COMP,
};

class Player
{
    public:
        Grid* grid;
        Player(int id, std::string name, PlayerTypes type);
        int getId();
        PlayerTypes getType();
        std::string getName();
    private:
        int _id{};
        PlayerTypes _type{};
        std::string _name{};
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
