#include <string>
#include <format>
#include "welcome.h"
#include "tools.h"
#include "fman.h"
#include "player.h"

using std::string, std::format;

void Welcome::print()
{
    Fman::playAnim("welcome", false, false);
}

Player* Welcome::selectEnemy()
{
    print();
    string ans = _console.input("To play with: human => H; computer => C");
    ans = Tools::lower(ans);

    if (_console.isAnswer(ans, "(h|human)")) {
        return new Human("PLAYER_2", PlayerTypes::HUMAN);
    }
    else if (_console.isAnswer(ans, "(c|comp|computer)")) {
        return new Comp("COMP", PlayerTypes::COMP);
    }
    else {
        _askAgain(format("There's no such user as \"{}\"!", ans));
        return selectEnemy();
    }
}

void Welcome::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
}
