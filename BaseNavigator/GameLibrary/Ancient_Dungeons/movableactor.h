#ifndef MOVABLEACTOR_H
#define MOVABLEACTOR_H

#include<staticdestroyableactor.h>
#include<ray.h>
class MovableActor:public StaticDestroyableActor
{
    protected:

public:
    MovableActor(std::vector<std::vector<QImage> >, Ray);
    virtual Sprite getSprite(QPointF,std::vector<std::vector<QRectF> > ,int,int);
};

#endif // MOVABLEACTOR_H
