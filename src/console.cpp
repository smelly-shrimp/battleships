#include <iostream>
#include <regex>
#include <vector>
#include "console.h"

using namespace std;

string Console::input()
{
    string arg;
    cin >> arg;
    return arg;
}

bool Console::isAnswer(string arg, string valid) {
    regex re(valid);
    regex_match(arg.c_str(), re);

    return false;
}
