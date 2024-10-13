#include <iostream>
#include "welcome.h"
#include "fman.h"

using namespace std;

void Welcome::print()
{
    Fman::playAnim("welcome", false);
    string ans = console.input("To play with: player => P; computer => C");
    if (console.isAnswer(ans, "(p|player)")) {

    }
    else if (false) {

    }
    else {}
}
