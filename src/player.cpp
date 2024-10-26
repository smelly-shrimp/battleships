#include <string>
#include "player.h"

using namespace std;

Player::Player(string name, PlayerTypes type)
{
    grid = new Grid();
    _type = type;
    _name = name;
}

PlayerTypes Player::getType()
{
    return _type;
}

string Player::getName()
{
    return _name;
}
