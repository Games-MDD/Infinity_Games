#ifndef WALLTEXTUREFACTORY_H
#define WALLTEXTUREFACTORY_H

#include<QImage>
class WallTextureFactory
{
public:
      QImage operator()(QColor,bool);
};

#endif // WALLTEXTUREFACTORY_H
