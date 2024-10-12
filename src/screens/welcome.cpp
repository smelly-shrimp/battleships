#include <iostream>
#include "welcome.h"
#include "fman.h"

using namespace std;

void Welcome::print()
{
    for (string f : Fman::read("welcome")) {
        cout << f << endl;
    }
}
