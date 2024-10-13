#include <iostream>
#include "welcome.h"
#include "tools.h"
#include "fman.h"

using namespace std;

void Welcome::_validate(string ans)
{
    if (console.isAnswer(ans, "(p|player)")) {
        cout << "PLAYER" << endl;
    }
    else if (console.isAnswer(ans, "(c|comp|computer)")) {
        cout << "COMPUTER" << endl;
    }
    else {
        print();
        console.drawLine("\x1B[31m", true);
        // cout << "Do you 'shun fancy things like electicity?'" << endl << endl;
        cout << "As I can see, you're 'Livin' in an Amish paradise'" << endl;

        Tools::waitMs(1500);

        Tools::clearConsole();
        print();
        _validate(console.input("Try Again... To play with: player => P; computer => C"));
    }
}

void Welcome::enemyIn()
{
    _validate(console.input("To play with: player => P; computer => C"));
}

void Welcome::print()
{
    Fman::playAnim("welcome", false);
}
