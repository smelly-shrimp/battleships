#include <iostream>
#include "end.h"
#include "fman.h"
#include "tools.h"
#include "game.h"

using std::cout, std::format, std::string;

void End::print()
{
    _printScores();
    // Fman::playAnim("end", true, false);
    _console.drawInfo("Congrats!", InfoType::DEF);
    Fman::playAnim("transition", true, true);
    Fman::playAnim("welcome", true, false);
}

void End::update()
{
    print();
}

bool End::isPlayAgain()
{
    const string ans{Tools::lower(_console.input("To play again => A"))};

    if (_console.isAnswer(ans, "(a|again)")) return true;
    else return false;
}

void End::_printScores()
{
    cout << Tools::insertChars("\n", 8);
    _console.center(format("congrats {}! You win!\n", Game::getWinner()));
    _console.center(format("PLAYER_1: {} wins\n", Game::getPlayerPoints(0)));
    _console.center(format("PLAYER_2: {} wins\n", Game::getPlayerPoints(1)));
    _console.center(format("COMP: {} wins\n", Game::getPlayerPoints(2)));
    _console.center(format("time: {}", Game::getTime()));
}
