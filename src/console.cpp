#include <array>
#include <iostream>
#include <regex>
#include <string>

#include "console.h"
#include "fman.h"
#include "game.h"
#include "tools.h"

using std::array, std::cin, std::cout, std::format, std::getline, std::regex, std::string;

string Console::input(string msg)
{
    string arg{};
    
    drawInfo(msg, InfoType::IN);
    getline(cin, arg);

    return arg;
}

bool Console::isAnswer(string arg, string valid) {
    regex re(valid);
    return regex_match(arg.c_str(), re);
}

void Console::drawInfo(string msg, InfoType type)
{
    _drawBar("", type, false);
    cout << msg << '\n';
    if (type == InfoType::IN) cout << Game::getCurrPlayer()->getName() << " % ";
    else getc(stdin);
}

void Console::drawHeader(string msg)
{
    cout << "\n\n";
    _drawBar(msg, InfoType::DEF, true);
}

void Console::drawShipList(bool isArrange, bool isComp)
{
    array<string, 4> names{ "four-masted  ", "three-masted ", "two-masted   ", "single-masted" };

    drawHeader(format("{} {}", Game::getCurrPlayer()->getName(), (isArrange ? "ARRANGING" : "SHOOTING")));

    Grid* grid1{};
    Grid* grid2{};
    if (isComp) {
        grid1 = Game::getCurrEnemy()->grid;
        grid2 = Game::getCurrPlayer()->grid;
    }
    else {
        grid1 = Game::getCurrPlayer()->grid;
        grid2 = Game::getCurrEnemy()->grid;
    }

    int curr{};
    for (int i{}; i < names.size(); i++) {
        cout << "  " << names.at(i) << ' ';

        for (int j{}; j <= i && curr < grid1->getShipList().size(); j++) {
            cout << (isArrange ? (grid1->getShipList().at(curr)->isUsed() ?  "██ " : "▁▁ ")
                                 : (grid2->getShipList().at(curr)->isSunk() ? "██ " : "▁▁ "));
            curr++;
        }
        cout << '\n';
    }
    cout << '\n';
}

void Console::drawGrid(bool isArrange, bool isComp)
{
    isArrange  ?
        cout << "  ┌───┬───────── OCEAN GRID ──────────┐\n"
             << "  │   │ 01 02 03 04 05 06 07 08 09 10 │\n"
             << "  ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤\n"
      : cout << "  ┌───┬───────── OCEAN GRID ──────────┐  ┌───┬──────── TARGET GRID ──────────┐\n"
             << "  │   │ 01 02 03 04 05 06 07 08 09 10 │  │   │ 01 02 03 04 05 06 07 08 09 10 │\n"
             << "  ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤  ├───┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼─┤\n";

    Grid* grid1{};
    Grid* grid2{};
    if (isComp) {
        grid1 = Game::getCurrEnemy()->grid;
        grid2 = Game::getCurrPlayer()->grid;
    }
    else {
        grid1 = Game::getCurrPlayer()->grid;
        grid2 = Game::getCurrEnemy()->grid;
    }
    
    for (int i{}; i < grid1->getGrid().size(); i++) {
        cout << "  │ " << static_cast<char>(65 + i) << " ┼ ";

        for (int j{}; j < grid1->getGrid().size(); j++) {
            cout << grid1->asString(grid1->getSquare(i, j));
        }

        if (!isArrange) {
            cout << "│";

            cout << "  │ " << static_cast<char>(65 + i) << " ┼ ";
            for (int j{}; j < grid2->getGrid().size(); j++) {
                cout << grid2->asString(grid2->getSquare(i, j), true);
            }
        }

        cout << "│\n";
    }

    cout << "  └" << Tools::insertChars("─", 35) << "┘";
    cout << (isArrange ? "\n" : format("  └{}┘\n", Tools::insertChars("─", 35)));
}

void Console::cover()
{
    Fman::playAnim(Game::getCurrPlayer()->getName() == "PLAYER_1" ? "player2_round" : "player1_round", false, false);
    drawInfo("ENTER to proceed", InfoType::DEF);
}

void Console::_drawBar(string msg, InfoType type, bool isHeader)
{
    InfoData d{_getInfoData(type)};

    int spaceReq{static_cast<int>((isHeader ? msg : d.msg).length() + 6)};
    int lSide{80 / 2 - spaceReq / 2};
    int rSide{lSide - spaceReq % 2};

    cout << d.color;

    cout << Tools::insertChars("━", lSide);
    cout << " » " << (isHeader ? msg : d.msg) << " « ";
    cout << Tools::insertChars("━", rSide);

    cout << Tools::ft["endf"];
}

InfoData Console::_getInfoData(InfoType type)
{   
    switch (type)
    {
    case InfoType::SUCC:
        return { "INFO", Tools::ft["green"] };
    case InfoType::WARN:
        return { "WARNING", Tools::ft["yellow"] };
    case InfoType::ERR:
        return { "ERROR", Tools::ft["red"] };
    case InfoType::IN:
        return { "", Tools::ft["magenta"] };
    default:
        return { "INFO", "" };
    }
}
