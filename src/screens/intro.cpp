#include <iostream>
#include <chrono>
#include <thread>
#include "intro.h"
#include "game.h"
#include "fman.h"

using namespace std;

void Intro::print()
{
    for (string f : Fman::read("intro")) {
        printf("\033[2J");
        cout << f << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    Game::setGameState(GameStates::WELCOME);
}
