#include <iostream>
#include <regex>
#include <vector>
#include "console.h"

using namespace std;

string Console::input(string msg)
{
    for (int i = 0; i < 80; i++) cout << "\u2594"; cout << endl;

    cout << msg << endl;
    string arg;
    cout << "ROOT $ ";
    cin >> arg;
    return arg;
}

bool Console::isAnswer(string arg, string valid) {
    regex re(valid);
    regex_match(arg.c_str(), re);

    return false;
}
