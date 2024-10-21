#include <iostream>
#include <regex>
#include "console.h"
#include "tools.h"
#include "game.h"

using std::cout, std::cin, std::getline, std::string, std::regex;

string Console::input(string msg)
{
    _drawLine(Tools::colors["magenta"]);

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

void Console::drawInfo(std::string msg)
{
    _drawLine(Tools::colors["green"], false);
    cout << msg << " (ENTER to proceed)\n";
    getc(stdin);
}

void Console::drawError(string msg)
{
    _drawLine(Tools::colors["red"], true);
    cout << msg << " (ENTER to proceed)\n";

    getc(stdin);
}

void Console::drawHeader(std::string action, bool isTop)
{
    int spaceReq = action.length() + 6;
    int lSide{80 / 2 - spaceReq / 2};
    int rSide{lSide - spaceReq % 2};

    cout << "\n" << Tools::insertChars("━", lSide) << " » " << action << " « " << Tools::insertChars("━", rSide) << "\n";
    if (isTop) cout << "\n";
}

void Console::_drawLine(string color, bool isError)
{
    cout << color;

    if (isError) drawHeader("ERROR");
    else cout << Tools::insertChars("━", 80);
    cout << Tools::colors["endf"];
}
