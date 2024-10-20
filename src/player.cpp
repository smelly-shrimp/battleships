#include <string>
#include "player.h"

using namespace std;

Player::Player(string name)
{
    _name = name;
}

string Player::getName()
{
    return _name;
}
