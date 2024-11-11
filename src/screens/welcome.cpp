#include <string>
#include <format>
#include "welcome.h"
#include "tools.h"
#include "fman.h"
#include "player.h"
#include "game.h"

using std::string, std::format;

void Welcome::print()
{
    Fman::playAnim("welcome", false, false);
}

void Welcome::update()
{
    Game::setCurrPlayer(new Human(0, "PLAYER_1", PlayerTypes::HUMAN));
    Game::setCurrEnemy(selectEnemy());
}

Player* Welcome::selectEnemy()
{
    print();
    string ans = _console.input("To play with: human => H; computer => C");
    ans = Tools::lower(ans);

    if (_console.isAnswer(ans, "(h|human)")) {
        return new Human(1, "PLAYER_2", PlayerTypes::HUMAN);
    }
    else if (_console.isAnswer(ans, "(c|comp|computer)")) {
        return new Comp(2, "COMP", PlayerTypes::COMP);
    }
    else {
        print();
        _console.drawInfo(format("There's no such user as \"{}\"!", ans), InfoType::ERR);
        return selectEnemy();
    }
}
