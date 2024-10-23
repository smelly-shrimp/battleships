#include <iostream>
#include <array>
#include <format>
#include <regex>
#include "shooting.h"
#include "game.h"
#include "console.h"
#include "tools.h"

#define OCCUP -1
#define EMPTY 0
#define SHIP 1
#define MISS 2
#define HIT 3
#define SUNK 4

using std::cout, std::array, std::string, std::format, std::regex, std::smatch, std::stoi;

void Shooting::print()
{
    auto pgrid{Game::getCurrPlayer()->grid};
    auto egrid{Game::getCurrEnemy()->grid};
    array<string, 4> names{ "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    _console.drawHeader(format("ATTACKING {}", Game::getCurrEnemy()->getName()), true);

    int curr{};
    for (int i{}; i < names.size(); i++) {
        cout << Tools::insertChars(" ", 2) << names.at(i) << " ";

        for (int j{}; j <= i && curr < pgrid.getShipList().size(); j++) {
            cout << (pgrid.getShipList().at(curr)->isSink() ? "██" : "▁▁");
            curr++;
        }

        cout << "\n";
    }

    cout << "\n";

    cout << Tools::insertChars(" ", 2) << "┌───┬───────── OCEAN GRID ──────────┐ ┌───┬──────── TARGET GRID ──────────┐\n"
         << Tools::insertChars(" ", 2) << "│   │ 01 02 03 04 05 06 07 08 09 10 │ │   │ 01 02 03 04 05 06 07 08 09 10 │\n"
         << Tools::insertChars(" ", 2) << "├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤ ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤\n";

    for (int i{}; i < pgrid.getGrid().size(); i++) {
        cout << "  │ " << char(65 + i) << " ┼ ";
        for (int j{}; j < pgrid.getGrid().size(); j++) {
            cout << pgrid.asString(pgrid.getSquare(i, j));
        }
        cout << "│";

        cout << " │ " << char(65 + i) << " ┼ ";
        for (int j{}; j < egrid.getGrid().size(); j++) {
            cout << egrid.asString(egrid.getSquare(i, j), true);
        }
        cout << "│";

        cout << "\n";
    }

    cout << Tools::insertChars(" ", 2) << "└" << Tools::insertChars("─", 35) << "┘"
         << " └" << Tools::insertChars("─", 35) << "┘\n";
}

void Shooting::selectShot()
{
    _selectShotPos();
}

void Shooting::_selectShotPos()
{
    print();

    string ans = _console.input("To shot: <a-j><1-10>");

    regex rex{"(([a-j])([1-9]|10))"};
    smatch matches;

    if (regex_match(ans, matches, rex)) {
        string rowNe = matches[2];
        string colNe = matches[3];
        int row = int(tolower(matches[2].str().c_str()[0])) - 97;
        int col = stoi(matches[3].str().c_str()) - 1;

        int val = Game::getCurrEnemy()->grid.getSquare(row, col);

        if (val >= 8 && val % 8 == 0) {
            Game::getCurrEnemy()->grid.setSquare(row, col, HIT);
            print();

            Ship* ship = Game::getCurrPlayer()->grid.getShipByVal(val);
            if (ship->getLen() > 1) {
                ship->setLen(ship->getLen() - 1);

                _console.drawInfo(
                    format("You hit the ship on {}{}{}{}!",
                    Tools::ft["underline"], rowNe, colNe, Tools::ft["endf"])
                );
            }
            else {
                ship->sink();
                int orient = ship->getOrient();

                for (int i{}; i < ship->getLen(); i++) {
                    Game::getCurrEnemy()->grid.setSquare(
                        (orient == 0 ? row : row + i), (orient == 0 ? col + i : col),
                        SUNK
                    );
                }

                _console.drawInfo("You sunk the ship!");
            }

            print();
            _selectShotPos();
        }
        else if (val == MISS || (val >= 8 && val % 8 == 0)) {
            _askAgain("You cannot shot to square which has already been shoted!");
            _selectShotPos();
        }
        else {
            Game::getCurrEnemy()->grid.setSquare(row, col, MISS);
            print();
            _console.drawInfo("You missed!");
        }

        // if (val >= 8 && val % 8 == 0) { // ship
        //     Game::getCurrPlayer()->grid.setSquare(row, col, HIT);
        //     // Game::getCurrEnemy()->grid.setSquare(row, col, HIT_OWN);
        //     // Game::getCurrPlayer()->grid.setSquare(row, col, HIT);

        //     Ship* ship = Game::getCurrPlayer()->grid.getShipByVal(val);
        //     print();
        //     if (ship->getLen() > 0) {
        //         ship->setLen(ship->getLen() - 1);

        //         _console.drawInfo(
        //             format("You hit the ship on {}{}{}{}!",
        //             Tools::ft["underline"], rowNe, colNe, Tools::ft["endf"])
        //         );
        //     }
        //     else _console.drawInfo("You sunk the ship on!");

        //     print();
        //     _selectShotPos();
        //     return;
        // }
        // else if (val == HIT || val == MISS) { // shoted again
        //     _askAgain("You cannot shot to already shot square!");
        //     _selectShotPos();
        //     return;
        // }
        // else { // miss
        //     Game::getCurrPlayer()->grid.setSquare(row, col, MISS);
        //     print();
        //     _console.drawInfo("You missed!");
        // }

        Game::changePlayers();
    }
    else {
        _askAgain("Wrong position");
        _selectShotPos();
    }
}

void Shooting::_askAgain(string msg)
{
    print();
    _console.drawError(msg);
}
