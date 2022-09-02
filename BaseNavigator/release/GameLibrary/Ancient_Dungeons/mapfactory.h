#ifndef MAPFACTORY_H
#define MAPFACTORY_H

#include <Map.h>
class MapFactory
{
public:
    Map* operator ()(QImage);
};

#endif // MAPFACTORY_H
