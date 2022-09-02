#ifndef PADDLE_H
#define PADDLE_H

#include <QImage>
#include <QRect>
class Paddle {
public:
  Paddle(const int, const int);
  ~Paddle();

public:
  void resetState();
  void move();
  void setDx(int);
  QRect getRect();
  QImage &getImage();

private:
  QImage image;
  QRect rect;
  qint32 dx;

public:
  static const int INITIAL_X_PR = 50;
  static const int INITIAL_Y_PR = 80;
  const int INITIAL_X;
  const int INITIAL_Y;
};

#endif // PADDLE_H
