#include <array>
#include <string>
#include "player.h"

using std::array, std::string;

Player::Player(string name, PlayerTypes type)
{
    grid = new Grid();
    _type = type;
    _name = name;
    srand(time(0));
}

PlayerTypes Player::getType()
{
    return _type;
}

string Player::getName()
{
    return _name;
}

// ShipPos Comp::arrange()
// {
//     int row{}, col{};
//     int orient{};

//     row = rand() % 10;
//     col = rand() % 10;
//     orient = rand() % 2;

//     return {row, col, orient};
// }
