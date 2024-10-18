#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;

class Ship
{
    protected:
        string _type;
        int _length;
        bool _isUsed;
        bool _isShotDown;
    public:
        Ship(int length);
        string getType();
        int getLength();
        bool isUsed();
        void shotDown();
        void use();
};

#endif // !SHIP_H
