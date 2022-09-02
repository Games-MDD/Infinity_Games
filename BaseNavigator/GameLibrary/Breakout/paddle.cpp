#include "paddle.h"

Paddle::Paddle(const int widht, const int heigth)
    : INITIAL_X(widht * Paddle::INITIAL_X_PR / 100),
      INITIAL_Y(heigth * Paddle::INITIAL_Y_PR / 100)

{
  dx = 0;
  image.load(":/new/Images/paddle.png");
  rect = image.rect();
  resetState();
}

Paddle::~Paddle() {}

void Paddle::setDx(int x) { dx = x; }

void Paddle::move() {
  int x = rect.x() + dx;
  int y = rect.top();

  rect.moveTo(x, y);
}

void Paddle::resetState() { rect.moveTo(INITIAL_X, INITIAL_Y); }

QRect Paddle::getRect() { return rect; }

QImage &Paddle::getImage() { return image; }
