#include <iostream>
#include <sstream>
#include "end.h"
#include "fman.h"
#include "tools.h"
#include "game.h"

using std::cout, std::format, std::stringstream, std::string;

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
    int time{Game::getTime()};
    stringstream ss;

    if (time > 60) {
        int m{time / 60};
        int s{time % 60};

        ss << m << "m " << s << "s";
    }
    else ss << time << "s";


    cout << Tools::insertChars("\n", 8);
    _console.center(format("Congrats {}{}{}! You win!", Tools::ft["magenta"],
        Game::getCurrPlayer()->getName(), Tools::ft["endf"]));
    _console.center(format("PLAYER_1: {} wins", Game::getPlayerPoints(0)));
    _console.center(format("PLAYER_2: {} wins", Game::getPlayerPoints(1)));
    _console.center(format("COMP: {} wins", Game::getPlayerPoints(2)));
    _console.center(format("time: {}", ss.str()));
    cout << Tools::insertChars("\n", 8);
}
