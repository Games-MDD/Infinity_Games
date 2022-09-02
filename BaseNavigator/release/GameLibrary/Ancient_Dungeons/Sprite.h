#ifndef SPRITE_H
#define SPRITE_H
#include<QImage>
#include<QtDebug>
#include<QPointF>
#include"Charactor.h"
struct Sprite
{
    QImage *Texture;
    QPointF Position;
    int Texture_size;
    Sprite(QImage img,QPointF position)
    {
        Texture=new QImage(img);
        Position=position;
        Texture_size=img.width();
    }

};

#endif // SPRITE_H
