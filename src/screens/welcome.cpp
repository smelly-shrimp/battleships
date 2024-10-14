#include <iostream>
#include "welcome.h"
#include "tools.h"
#include "fman.h"
#include "player.h"

using namespace std;

Player* Welcome::inputEnemy()
{
    string ans = console.input("To play with: human => H; computer => C");

    if (console.isAnswer(ans, "(h|human)")) {
        return new Human("PLAYER_2");
    }
    else if (console.isAnswer(ans, "(c|comp|computer)")) {
        return new Comp("COMP");
    }
    else {
        print();
        console.drawLine("\x1B[31m", true);
        cout << "As I can see, you're 'Livin' in an Amish paradise'" << endl;

        Tools::waitMs(1500);

        Tools::clearConsole();
        print();
        inputEnemy();
    }
}

void Welcome::print()
{
    Fman::playAnim("welcome", false, false);
}
