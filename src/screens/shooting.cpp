#include <iostream>
#include "shooting.h"
#include "game.h"
#include "console.h"

void Shooting::print()
{
    std::cout << Game::getCurrPlayer()->grid.getGrid();
}

void Shooting::inputShot()
{
    std::string ans = _console.input("To shot: <a-j><1-10>", Game::getCurrPlayer()->getName());
}
