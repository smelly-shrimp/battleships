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

class Human
{
    
};

class Computer
{

};

#endif // !PLAYER_H
