#include <iostream>
#include <vector>
#include <fstream>
#include <format>
#include "fman.h"

using namespace std;

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

void Fman::playAnim()
{
    cout << "play anim" << endl;
}
