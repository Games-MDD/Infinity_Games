#include "movableactor.h"

MovableActor::MovableActor(std::vector<std::vector<QImage> > frameArr, Ray ray):
    StaticDestroyableActor(frameArr,ray.getStartPoint()),
    mainRay(ray)
{

}
Sprite MovableActor::getSprite(QPointF CharactorPosition,std::vector<std::vector<QRectF> > RectArr,int width,int heigth){
    if(destroed)
return Sprite(FramesArr[0][0],QPointF(-1,-1));
Sprite answer=Sprite(FramesArr[0][0],Position);
Position.setX(Position.x()+mainRay.getDirection().x());
Position.setY(Position.y()+mainRay.getDirection().y());
mainRay.setStartPoint(Position);
bool reversDir=false;
if(Position.x()<0 || Position.y()<0 || Position.x()>=width || Position.y()>=heigth)
reversDir=true;
for(size_t i=0;i<RectArr.size();++i)
for(size_t j=0;j<RectArr[i].size();++j)
{
    if(Position.x()>=RectArr[i][j].left() && Position.x()<=RectArr[i][j].right())
        if(Position.y()>=RectArr[i][j].top() && Position.y()<=RectArr[i][j].bottom())
            reversDir=true;
}
if(reversDir)
mainRay.Scale(-1);
return answer;
}
