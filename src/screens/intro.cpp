#include "intro.h"
#include "game.h"
#include "fman.h"

void Intro::print()
{
    Fman::playAnim("intro", false, false);
    Game::setGameState(GameStates::WELCOME);
}
