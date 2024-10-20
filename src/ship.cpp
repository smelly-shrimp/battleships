#include <string>
#include "ship.h"

using namespace std;

Ship::Ship(int length)
{
    _length = length;
}

string Ship::getType()
{
    return _type;
}

int Ship::getLength()
{
    return _length;
}

bool Ship::isUsed()
{
    return _isUsed;
}

void Ship::shotDown()
{
    _isShotDown = true;
}

void Ship::use()
{
    _isUsed = true;
}
