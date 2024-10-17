#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;

class Ship
{
    private:
        string _type;
        int _length;
        bool _isShotDown;
    public:
        string getType();
        int getLength();
        void shotDown();
};

class OneMasted : public Ship
{
    private:
        string _type = "one-masted";
        int _length = 1;
};

class TwoMasted : public Ship
{
    private:
        string _type = "two-masted";
        int _length = 2;
};

class ThreeMasted : public Ship
{
    private:
        string _type = "three-masted";
        int _length = 3;
};

class FourMasted : public Ship
{
    private:
        string _type = "four-masted";
        int _length = 4;
};

#endif // !SHIP_H
