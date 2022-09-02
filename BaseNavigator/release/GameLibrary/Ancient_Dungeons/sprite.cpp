#include "sprite.h"

Sprite::Sprite()
{

}
Sprite::Sprite(QImage img,QPointF position)
{
    Texture=new QImage(img);

}
