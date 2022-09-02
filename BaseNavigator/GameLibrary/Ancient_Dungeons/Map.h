#ifndef MAP_H
#define MAP_H
#include <QtWidgets>
#include <vector>
struct Map {
    std::vector<std::vector<uint> > wallMap;
    std::vector<std::vector<QColor> > textureMap;
    std::vector<std::vector<uint> > ceilMap;
    std::vector<std::vector<uint> > floorMap;
    int width,height;
};

#endif // MAP_H
