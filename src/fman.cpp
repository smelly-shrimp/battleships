#include <iostream>
#include <vector>
#include <fstream>
#include <format>
#include <chrono>
#include <thread>
#include "fman.h"

using namespace std;

void Fman::_pingPong(vector<string> f, int i)
{
    cout << f.at(i) << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    if (i < f.size() - 1) _pingPong(f, i + 1);
    cout << f.at(i) << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

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

void Fman::playAnim(string file, bool isPingPong)
{
    vector<string> anim = Fman::read(file);

    if (isPingPong) _pingPong(anim, 0);
    else {
        for (string f : anim) {
            printf("\033[2J");
            cout << f << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }

    _frames.clear();
}
