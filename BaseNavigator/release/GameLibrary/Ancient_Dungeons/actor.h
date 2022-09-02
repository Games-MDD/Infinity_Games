#ifndef ACTOR_H
#define ACTOR_H

#include <Charactor.h>
#include <Sprite.h>
class Actor {
    protected:
  QPointF Position;
  std::vector<std::vector<QImage> > FramesArr;

public:
  virtual ~Actor(){

  }
  virtual void setPosition(QPointF position) {
    Position = position;
  }

  virtual Sprite getSprite(Charactor&)=0;
};

#endif // ACTOR_H
