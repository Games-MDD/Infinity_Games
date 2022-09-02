#ifndef STATICDESTROYABLEACTOR_H
#define STATICDESTROYABLEACTOR_H

#include<staticactor.h>
class StaticDestroyableActor:public Actor
{
public:
    ~StaticDestroyableActor(){

    }
    StaticDestroyableActor(std::vector<std::vector<QImage> >,QPointF);
    virtual Sprite getSprite(QPointF,std::vector<std::vector<QRectF> > ,int,int);

};

#endif // STATICDESTROYABLEACTOR_H
