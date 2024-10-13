#include "welcome.h"
#include "fman.h"

using namespace std;

void Welcome::print()
{
    Fman::playAnim("welcome", false);
}
