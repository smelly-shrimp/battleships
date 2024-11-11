#include "intro.h"
#include "fman.h"

void Intro::print()
{
    Fman::playAnim("intro", false, false, 150);
}

void Intro::update()
{
    print();
}
