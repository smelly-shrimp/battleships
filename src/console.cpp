#include <iostream>
#include <regex>
#include <vector>
#include "console.h"
#include "tools.h"
#include "game.h"

using namespace std;

string Console::input(string msg, string name)
{
    _drawLine();

    cout << msg << endl;
    string arg;
    cout << name << " $ ";
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
    cout << msg << endl;

    Tools::waitMs(1000);
    Tools::clearConsole();
}

void Console::drawError(string msg)
{
    _drawLine(Tools::colors["red"], true);
    cout << msg << endl;

    Tools::waitMs(2000);
    Tools::clearConsole();
}

void Console::_drawChars(int length, string color)
{
    for (int i = 0; i < length; i++) cout << color << "\u2594";
}

void Console::_drawLine(string color, bool isError)
{
    if (isError) {
        _drawChars(36, color);
        cout << " ERROR ";
        _drawChars(36, color);
    }
    else _drawChars(80, color);

    cout << Tools::colors["endf"] << endl;
}
