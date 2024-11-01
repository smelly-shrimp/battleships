#include <iostream>
#include <array>
#include <regex>
#include "console.h"
#include "tools.h"
#include "game.h"

using std::array, std::cout, std::cin, std::getline, std::string, std::regex;

string Console::input(string msg)
{
    _drawLine(Tools::ft["magenta"]);

    cout << msg << "\n";
    string arg;
    cout << Game::getCurrPlayer()->getName() << " $ ";

    getline(cin, arg);

    return arg;
}

bool Console::isAnswer(string arg, string valid) {
    regex re(valid);
    return regex_match(arg.c_str(), re);
}

void Console::drawInfo(std::string msg, bool isBad)
{
    if (isBad) _drawLine(Tools::ft["yellow"], false);
    else _drawLine(Tools::ft["green"], false);
    cout << msg << " (ENTER to proceed)\n";
    getc(stdin);
}

void Console::drawError(string msg)
{
    _drawLine(Tools::ft["red"], true);
    cout << msg << " (ENTER to proceed)\n";
    getc(stdin);
}

void Console::drawHeader(string action, bool isTop)
{
    int spaceReq = action.length() + 6;
    int lSide{80 / 2 - spaceReq / 2};
    int rSide{lSide - spaceReq % 2};

    if (isTop) cout << "\n";
    cout << Tools::insertChars("━", lSide) << " » " << action << " « " << Tools::insertChars("━", rSide) << "\n";
}

void Console::drawShipList(string msg, bool isArrange, bool isHidden)
{
    array<string, 4> names{ "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    isHidden ? drawHeader("ENTER TO PROCEED", true) : drawHeader(msg, true);

    int curr{};
    for (int i{}; i < names.size(); i++) {
        cout << "  " << names.at(i) << " ";

        for (int j{}; j <= i && curr < Game::getCurrPlayer()->grid->getShipList().size(); j++) {
            if (isHidden) {
                cout << "?? ";
            }
            else {
                if (isArrange) cout << (Game::getCurrPlayer()->grid->getShipList().at(curr)->isUsed() ? "██ " : "▁▁ ");
                else cout << (Game::getCurrEnemy()->grid->getShipList().at(curr)->isSink() ? "██ " : "▁▁ ");
            }
            curr++;
        }

        cout << "\n";
    }

    cout << "\n";
}

void Console::drawGrid(bool isArrange, bool isComp, bool isHidden)
{
    if (isArrange) {
        cout << "  ┌───┬───────── OCEAN GRID ──────────┐\n"
             << "  │   │ 01 02 03 04 05 06 07 08 09 10 │\n"
             << "  ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤\n";
    }
    else {
        cout << "  ┌───┬───────── OCEAN GRID ──────────┐ ┌───┬──────── TARGET GRID ──────────┐\n"
             << "  │   │ 01 02 03 04 05 06 07 08 09 10 │ │   │ 01 02 03 04 05 06 07 08 09 10 │\n"
             << "  ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤ ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤\n";
    }

    Grid* pgrid{};
    Grid* egrid{};
    if (isComp) {
        pgrid = Game::getCurrEnemy()->grid;
        egrid = Game::getCurrPlayer()->grid;
    }
    else {
        pgrid = Game::getCurrPlayer()->grid;
        egrid = Game::getCurrEnemy()->grid;
    }
    
    for (int i{}; i < pgrid->getGrid().size(); i++) {
        cout << "  │ " << static_cast<char>(65 + i) << " ┼ ";

        for (int j{}; j < pgrid->getGrid().size(); j++) {
            cout << (isHidden ? "?? " : pgrid->asString(pgrid->getSquare(i, j)));
        }

        if (!isArrange) {
            cout << "│";

            cout << " │ " << static_cast<char>(65 + i) << " ┼ ";
            for (int j{}; j < egrid->getGrid().size(); j++) {
                cout << (isHidden ? "?? " : egrid->asString(egrid->getSquare(i, j), true));
            }
        }

        cout << "│\n";
    }

    cout << "  └" << Tools::insertChars("─", 35) << "┘";
    cout << (isArrange ? "\n" : format(" └{}┘\n", Tools::insertChars("─", 35)));
}

void Console::_drawLine(string color, bool isError)
{
    cout << color;

    if (isError) drawHeader("ERROR");
    else cout << Tools::insertChars("━", 80);
    cout << Tools::ft["endf"];
}
