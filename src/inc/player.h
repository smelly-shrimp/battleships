#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

enum squareStates
{
    EMPTY,
    SHOT,
};

class Player
{
    private:
        string _name;
        void _clear();
        squareStates grid[10][10];
    public:
        Player(string name);
        string getName();
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
