#include "movableconsumableactor.h"

MovableConsumableActor::MovableConsumableActor(std::vector<std::vector<QImage> > frameArr, Ray ray):
    MovableActor(frameArr,ray)
{

}
Sprite MovableConsumableActor::getSprite(QPointF CharactorPosition,std::vector<std::vector<QRectF> > RectArr,int width,int heigth){
    if(destroed)
return Sprite(FramesArr[0][0],QPointF(-1,-1));
Sprite answer=Sprite(FramesArr[0][0],Position);
Position.setX(Position.x()+mainRay.getDirection().x());
Position.setY(Position.y()+mainRay.getDirection().y());
mainRay.setStartPoint(Position);
bool needDestroy=false;
if(Position.x()<0 || Position.y()<0 || Position.x()>=width || Position.y()>=heigth)
needDestroy=true;
for(size_t i=0;i<RectArr.size();++i)
for(size_t j=0;j<RectArr[i].size();++j)
{
    if(Position.x()>=RectArr[i][j].left() && Position.x()<=RectArr[i][j].right())
        if(Position.y()>=RectArr[i][j].top() && Position.y()<=RectArr[i][j].bottom())
            needDestroy=true;
}
if(needDestroy)
Destroy();
return answer;
}
