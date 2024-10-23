#include <string>
#include "ship.h"

using std::map, std::string;

Ship::Ship(int id, int len)
{
    _id = 8 * id;
    _len = len;
    this->len = _len;
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
    return _len;
}

void Ship::setLen(int len)
{
    _len = len;
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

bool Ship::isSink()
{
    return _isSink;
}

bool Ship::isUsed()
{
    return _isUsed;
}

void Ship::sink()
{
    _isSink = true;
}

void Ship::use()
{
    _isUsed = true;
}
