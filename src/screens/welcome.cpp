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
        _console.drawError(format("There's no such user as {}!", ans));
        print();
        selectEnemy();
    }

    return 0;
}

int Welcome::selectArrangeMode()
{
    print();

    string ans = _console.input("To arrange: manual => M; automatic => A");
    ans = Tools::lower(ans);

    if (_console.isAnswer(ans, "(m|manual)")) return 0;
    else if (_console.isAnswer(ans, "(a|auto|automatic)")) return 1;
    else {
        printf("BAR");
        print();
        _console.drawError(format("There's no such mode as {}!", ans));
        print();
        selectArrangeMode();
    }

    return 0;
}
