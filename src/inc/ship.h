#ifndef SHIP_H
#define SHIP_H

#include <string>

class Ship
{
    protected:
        std::string _type;
        int _length;
        bool _isUsed;
        bool _isShotDown;
    public:
        Ship(int length);
        std::string getType();
        int getLength();
        bool isUsed();
        void shotDown();
        void use();
};

#endif // !SHIP_H
