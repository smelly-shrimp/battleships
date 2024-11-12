#include <string>
#include "ship.h"

using std::map, std::string;

Ship::Ship(int id, int len)
{
    _id = 8 * id;
}

int Ship::getId()
{
    return _id;
}

string Ship::getType()
{
    return _type;
}

int Ship::getLen()
{
    return _oLen;
}

void Ship::setLen(int len)
{
    _oLen = len;
}

void Ship::setPos(int row, int col)
{
    _pos["row"] = row;
    _pos["col"] = col;
}

map<string, int> Ship::getPos()
{
    return _pos;
}

void Ship::setOrient(int orient)
{
    _orient = orient;
}

int Ship::getOrient()
{
    return _orient;
}

bool Ship::isSunk()
{
    return _isSink;
    // return true;
}

bool Ship::isUsed()
{
    return _isUsed;
}

void Ship::use()
{
    _isUsed = true;
}

void Ship::hit()
{
    _len++;

    if (_len >= _oLen) _isSink = true;
}
