#ifndef SHIP_H
#define SHIP_H

#include <string>

class Ship
{
    public:
        Ship(int id, int length);
        int getId();
        std::string getType();
        int getLen();
        void setLen(int len);
        void setOrient(int orient);
        int getOrient();
        bool isSink();
        bool isUsed();
        void sink();
        void use();
    private:
        int _id;
        std::string _type;
        int _len;
        int _orient;
        bool _isUsed;
        bool _isSink;
};

#endif // !SHIP_H
