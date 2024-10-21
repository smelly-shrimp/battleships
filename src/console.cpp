#include <iostream>
#include <regex>
#include "console.h"
#include "tools.h"
#include "game.h"

using std::cout, std::cin, std::getline, std::string, std::regex;

string Console::input(string msg, string name)
{
    _drawLine(Tools::colors["magenta"]);

    cout << msg << "\n";
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
    cout << msg << "\n";

    Tools::waitMs(2000);
}

void Console::drawError(string msg)
{
    _drawLine(Tools::colors["red"], true);
    cout << msg << "\n";

    Tools::waitMs(2000);
    Tools::clearConsole();
}

void Console::_drawLine(string color, bool isError)
{
    cout << color;

    if (isError) {
        cout << Tools::insertChars("▔", 36);
        cout << " ERROR ";
        cout << Tools::insertChars("▔", 36);
    }
    else cout << Tools::insertChars("▔", 80);

    cout << Tools::colors["endf"] << "\n";
}
