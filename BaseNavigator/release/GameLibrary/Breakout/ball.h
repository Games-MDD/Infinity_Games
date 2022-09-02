#ifndef BALL_H
#define BALL_H

#include <QImage>
#include <QRect>

class Ball {

public:
  Ball(const int,const int);
  ~Ball();

public:
  void resetState();
  void autoMove();
  void setXDir(int);
  void setYDir(int);
  int getXDir();
  int getYDir();
  QRect getRect();
  QImage &getImage();

private:
  int xdir;
  int ydir;
  QImage image;
  QRect rect;
  static const int INITIAL_X_PR = 50;
  static const int INITIAL_Y_PR = 70;
  static const int RIGHT_EDGE_PR = 5;
   const int INITIAL_X = 230;
   const int INITIAL_Y = 355;
   const int RIGHT_EDGE = 300;
};

#endif // BALL_H
