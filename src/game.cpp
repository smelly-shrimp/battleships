#include "game.h"

void Game::setGameState(GameStates state)
{
    Game::_state = state;
}

GameStates Game::getGameState()
{
    return GameStates();
}
