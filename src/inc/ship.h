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
        bool isSink();
        bool isUsed();
        void sink();
        void use();
    private:
        int _id;
        std::string _type;
        int _len;
        bool _isUsed;
        bool _isSink;
};

#endif // !SHIP_H
