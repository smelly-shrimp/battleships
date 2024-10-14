#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "grid.h"
using namespace std;

class Player
{
    public:
        Player(string name);
        string getName();
    private:
        string _name;
        Grid grid;
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
