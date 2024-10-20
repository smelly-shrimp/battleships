#include <string>
#include "welcome.h"
#include "tools.h"
#include "fman.h"
#include "player.h"

using namespace std;

Player* Welcome::inputEnemy()
{
    string ans = _console.input("To play with: human => H; computer => C");
    ans = Tools::lower(ans);

    if (_console.isAnswer(ans, "(h|human)")) {
        return new Human("PLAYER_2");
    }
    else if (_console.isAnswer(ans, "(c|comp|computer)")) {
        return new Comp("COMP");
    }
    else {
        print();
        _console.drawError("As I can see, you're 'Livin' in an Amish paradise'");
        print();
        inputEnemy();
    }
}

void Welcome::print()
{
    Fman::playAnim("welcome", false, false);
}
