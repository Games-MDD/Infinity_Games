#ifndef MOVABLECONSUMABLEACTOR_H
#define MOVABLECONSUMABLEACTOR_H

#include<movableactor.h>
class MovableConsumableActor:public MovableActor
{
public:
    MovableConsumableActor(std::vector<std::vector<QImage> >, Ray);
    virtual Sprite getSprite(QPointF,std::vector<std::vector<QRectF> > ,int,int);
};

#endif // MOVABLECONSUMABLEACTOR_H
