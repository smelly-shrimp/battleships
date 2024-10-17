#include "ship.h"

string Ship::getType()
{
    return _type;
}

int Ship::getLength()
{
    return _length;
}

void Ship::shotDown()
{
    _isShotDown = true;
}
