#include <locale.h>
#include "game.h"

int main() {
    setlocale(LC_ALL, "");
    Game::setGameState(GameStates::WELCOME);
}
