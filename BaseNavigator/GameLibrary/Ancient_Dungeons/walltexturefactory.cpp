#include "walltexturefactory.h"
#include<QtDebug>
#include<QColor>
QImage WallTextureFactory::operator()(QColor textureType,bool isXProjection) {
  if (textureType == QColor::fromRgb(47,64,159).rgb())
      if(isXProjection)
    return QImage(":/walls/Resources/Wall/WALL14.bmp");
  else
       return QImage(":/walls/Resources/Wall/WALL15.bmp");
  if (textureType == QColor::fromRgb(255,255,0).rgb())
      if(isXProjection)
    return QImage(":/walls/Resources/Wall/WALL46.bmp");
  else
       return QImage(":/walls/Resources/Wall/WALL47.bmp");
  if (textureType == QColor::fromRgb(198,40,40).rgb())
      if(isXProjection)
    return QImage(":/walls/Resources/Wall/WALL32.bmp");
  else
       return QImage(":/walls/Resources/Wall/WALL33.bmp");
  if (textureType == QColor::fromRgb(245,127,23).rgb())
      if(isXProjection)
    return QImage(":/walls/Resources/Wall/WALL22.bmp");
  else
       return QImage(":/walls/Resources/Wall/WALL23.bmp");
  if (textureType == 4288891300)
      if(isXProjection)
    return QImage(":/walls/Resources/Wall/WALL64.bmp");
  else
       return QImage(":/walls/Resources/Wall/WALL65.bmp");
  if(isXProjection)
return QImage(":/walls/Resources/Wall/WALL0.bmp");
else
   return QImage(":/walls/Resources/Wall/WALL1.bmp");
}
