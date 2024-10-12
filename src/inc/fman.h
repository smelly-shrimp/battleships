#ifndef FMAN_H
#define FMAN_H

#include <iostream>
#include <vector>

using namespace std;

class Fman
{
    private:
        inline static vector<string> _frames;
        static void _pingPong(vector<string> f, int i);
    public:
        static vector<string> read(string file);
        static void playAnim(string file, bool isPingPong);
};

#endif // !FMAN_H
