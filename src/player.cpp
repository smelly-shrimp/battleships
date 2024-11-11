#include <array>
#include <string>
#include "player.h"

using std::array, std::string;

Player::Player(int id, std::string name, PlayerTypes type)
{
    grid = new Grid();
    _id = id;
    _type = type;
    _name = name;
}

int Player::getId()
{
    return _id;
}

PlayerTypes Player::getType()
{
    return _type;
}

string Player::getName()
{
    return _name;
}
