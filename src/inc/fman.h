#ifndef FMAN_H
#define FMAN_H

#include <iostream>
#include <vector>

using namespace std;

class Fman
{
    private:
        inline static vector<string> _frames;
    public:
        static vector<string> read(string file);
        void playAnim();
};

#endif // !FMAN_H
