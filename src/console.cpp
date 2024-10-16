#include <iostream>
#include <regex>
#include <vector>
#include "console.h"

using namespace std;

void Console::drawLine(string color, bool isError)
{
    if (isError) {
        _drawChars(36, color);
        cout << " ERROR ";
        _drawChars(36, color);
    }
    else _drawChars(80, color);
    
    cout << "\033[0m" << endl;
}

string Console::input(string msg)
{
    drawLine();

    cout << msg << endl;
    string arg;
    cout << "ROOT $ ";
    cin >> arg;

    return arg;
}

bool Console::isAnswer(string arg, string valid) {
    regex re(valid);
    return regex_match(arg.c_str(), re);
}

void Console::_drawChars(int length, string color)
{
    for (int i = 0; i < length; i++) cout << color << "\u2594";
}
