#include <iostream>
#include <regex>
#include <ctime>
#include <ctime>
#include <vector>
#include <fstream>
#include <format>
#include "fman.h"
#include "tools.h"

using std::cout, std::ifstream, std::ofstream, std::regex, std::vector, std::smatch, std::string;

vector<string> Fman::read(string file)
{
    ifstream framesFile(format("./src/anims/{}.anim", file));

    char ch;
    string f;
    while (framesFile.get(ch)) {
        if (ch != '$') {
            f.push_back(ch);
        }
        else {
            if (f[0] == '\n') {
                f.erase(0, 1);
            }

            f.erase(f.length()-1);
            _frames.push_back(f);
            f = "";
        }
    }

    framesFile.close();

    return _frames;
}

void Fman::playAnim(string file, bool isClear, bool isPingPong)
{
    vector<string> anim = Fman::read(file);

    if (isPingPong) _pingPong(anim, 0);
    else {
        for (string f : anim) {
            if (isClear) Tools::clearConsole();
            cout << f << '\n';
            if (anim.size() > 1) Tools::waitMs(500);
        }
    }

    _frames.clear();
}

void Fman::readData()
{
    ifstream data("data");

    regex id("#(.+)$");
    regex round("^ @round([1-9][0-9]*): (.+$)");

    smatch matches;
    string line;
    while (getline(data, line)) {
        if (regex_match(line, matches, id)) {
            string id = matches[1];
        }
        else if (regex_match(line, matches, round)) {
            string winner = matches[2];
        }
    }

    data.close();
}

void Fman::writeData()
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char time[50];
    strftime(time, 50, "%m.%d.%y %H.%M.%S", &datetime);

    ofstream data;
    data.open("data");
    data << "#" << time << ": ";
}

void Fman::_pingPong(vector<string> f, int i)
{
    cout << f.at(i) << '\n';
    Tools::waitMs(50);
    if (i < f.size() - 1) _pingPong(f, i + 1);
    cout << f.at(i) << '\n';
    Tools::waitMs(50);
}
