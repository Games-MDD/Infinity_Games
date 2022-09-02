#include "staticdestroyableactor.h"
StaticDestroyableActor::StaticDestroyableActor(
    std::vector<std::vector<QImage>> frameArr, QPointF position)
    : Actor(frameArr, position) {}
