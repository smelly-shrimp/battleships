#include <iostream>
#include "welcome.h"
#include "fman.h"

using namespace std;

void Welcome::print()
{
    for (string f : Fman::read("welcome")) {
        printf("\033[2J");
        cout << f << endl;
    }
}
