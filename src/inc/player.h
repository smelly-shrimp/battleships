#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "grid.h"
using namespace std;

class Player
{
    public:
        Grid grid;
        Player(string name);
        string getName();
    private:
        string _name;
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
