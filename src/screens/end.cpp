#include <iostream>
#include "end.h"
#include "fman.h"
#include "tools.h"

using std::string;

void End::print()
{
    Fman::playAnim("end", true, false);
    _console.drawInfo("...");
    Fman::playAnim("transition", true, true);
}

bool End::isPlayAgain()
{
    const string ans{Tools::lower(_console.input("To play again => A"))};

    if (_console.isAnswer(ans, "(a|again)")) return true;
    else return false;

    return false;
}

void End::saveScores()
{
}
