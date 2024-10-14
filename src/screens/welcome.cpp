#include <iostream>
#include "welcome.h"
#include "tools.h"
#include "fman.h"
#include "player.h"
#include "game.h"

using namespace std;

void Welcome::_validate(string ans)
{
    if (console.isAnswer(ans, "(h|human)")) {
        Game::p1 = new Human("PLAYER_1");
        Game::p2 = new Human("PLAYER_2");
    }
    else if (console.isAnswer(ans, "(c|comp|computer)")) {
        Game::p1 = new Human("PLAYER_1");
        Game::p2 = new Comp("COMP");
    }
    else {
        print();
        console.drawLine("\x1B[31m", true);
        cout << "As I can see, you're 'Livin' in an Amish paradise'" << endl;

        Tools::waitMs(1500);

        Tools::clearConsole();
        print();
        _validate(console.input("Try Again... To play with: human => H; computer => C"));
    }
}

void Welcome::enemyIn()
{
    _validate(console.input("To play with: human => H; computer => C"));
}

void Welcome::print()
{
    Fman::playAnim("welcome", false);
}
