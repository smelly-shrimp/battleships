#include <iostream>
#include <array>
#include <format>
#include <regex>
#include "shooting.h"
#include "game.h"
#include "console.h"
#include "tools.h"

#define HIT 1
#define MISS 3

using std::cout, std::array, std::string, std::format, std::regex, std::smatch, std::stoi;

void Shooting::print()
{
    auto grid{Game::getCurrPlayer()->grid};
    array<string, 4> names{ "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    _console.drawHeader(format("ATTACKING {}", Game::getCurrEnemy()->getName()), true);

    int curr{};
    for (int i{}; i < names.size(); i++) {
        cout << Tools::insertChars(" ", 2) << names.at(i) << " ";

        for (int j{}; j <= i && curr < grid.getShipList().size(); j++) {
            cout << (grid.getShipList().at(curr)->isSink() ? "██" : "▁▁");
            curr++;
        }

        cout << "\n";
    }

    cout << "\n";

    cout << Tools::insertChars(" ", 2) << "┌───┬───────── OCEAN GRID ──────────┐ ┌───┬──────── TARGET GRID ──────────┐\n"
         << Tools::insertChars(" ", 2) << "│   │ 01 02 03 04 05 06 07 08 09 10 │ │   │ 01 02 03 04 05 06 07 08 09 10 │\n"
         << Tools::insertChars(" ", 2) << "├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤ ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤\n";

    for (int i{}; i < grid.getGrid().size(); i++) {
        cout << Tools::insertChars(" ", 2) << "│ " << char(65 + i) << " ┼ ";
        for (int j{}; j < grid.getGrid().size(); j++) {
            cout << grid.asString(grid.getSquare(i, j));
        }
        cout << "│";

        cout << " │ " << char(65 + i) << " ┼ ";
        for (int j{}; j < grid.getGrid().size(); j++) {
            cout << grid.asString(grid.getSquare(i, j), true);
        }
        cout << "│\n";
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
        string colNe = matches[3];
        string rowNe = matches[2];
        int col = stoi(matches[3].str().c_str()) - 1;
        int row = int(tolower(matches[2].str().c_str()[0])) - 97;

        print();

        // int currSquare = Game::getCurrEnemy()->grid.getSquare(col, row);
        // cout << currSquare << "\n";
        // if (currSquare >= 8 && currSquare % 4 == 0) {
        //     Game::getCurrPlayer()->grid.setSquare(col, row, Game::getCurrPlayer()->grid.getSquare(col, row) + HIT);
        //     _console.drawInfo(format("You hit a ship on {}{}{}{}!", Tools::ft["underline"], rowNe, colNe, Tools::ft["endf"]));
        // }
        // // else if (currSquare % 4 == HIT) {

        // // }
        // else {
        //     Game::getCurrPlayer()->grid.setSquare(col, row, Game::getCurrPlayer()->grid.getSquare(col, row) + MISS);
        //     _console.drawInfo("You missed!");
        // }

        // switch (currSquare)
        // {
        //     case SHIP:
        //         // Game::getCurrPlayer()->grid.setSquare(col, row, 2);
        //         // Game::getCurrEnemy()->grid.setSquare(col, row, 3);
        //         _console.drawInfo(format("You hit a ship on {}{}{}{}!", Tools::ft["underline"], rowNe, colNe, Tools::ft["endf"]));
        //         _selectShotPos();
        //         break;
        //     // case MISS:
        //     //     _console.drawError("This square has been already been shoted!");
        //         // _askAgain(format("This square has been already been shoted!"));
        //     //     _selectShotPos();
        //         // break;
        //     default:
        //         // Game::getCurrPlayer()->grid.setSquare(col, row, MISS);
        //         _console.drawInfo("You missed!");
        //         break;
        // }
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
