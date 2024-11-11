#include <iostream>
#include "end.h"
#include "fman.h"
#include "tools.h"

using std::string;

void End::print()
{
    Fman::playAnim("end", true, false);
    _console.drawInfo("...", InfoType::DEF);
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
