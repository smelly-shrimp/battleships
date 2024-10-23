#include <string>
#include "ship.h"

using namespace std;

Ship::Ship(int id, int length)
{
    _id = 8 * id;
    _len = length;
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
