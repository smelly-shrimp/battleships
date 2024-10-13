#include "intro.h"
#include "game.h"
#include "fman.h"

using namespace std;

void Intro::print()
{
    Fman::playAnim("intro", false);
    Game::setGameState(GameStates::WELCOME);
}
