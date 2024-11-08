#include "intro.h"
#include "fman.h"

void Intro::print()
{
    Fman::playAnim("intro", false, false);
    Fman::playAnim("transition", false, true);
}

void Intro::update()
{
    print();
}
