#ifndef SHIP_H
#define SHIP_H

#include <map>
#include <string>

class Ship
{
    public:
        Ship(int id, int len);
        int getId();
        std::string getType();
        int getLen();
        void setLen(int len);
        void setPos(int row, int col);
        std::map<std::string, int> getPos();
        void setOrient(int orient);
        int getOrient();
        bool isSink();
        bool isUsed();
        void use();
        void hit();
    private:
        int _id{};
        std::string _type{};
        std::map<std::string, int> _pos{ { "row", 0 }, { "col", 0 } };
        int _len{};
        int _oLen{};
        int _orient{};
        bool _isUsed{};
        bool _isSink{};
};

#endif // !SHIP_H
