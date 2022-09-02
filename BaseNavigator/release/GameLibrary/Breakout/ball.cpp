#include "ball.h"
#include <cmath>
Ball::Ball(const int width, const int height)
    : INITIAL_X(width * INITIAL_X_PR / 100),
      INITIAL_Y(height * INITIAL_Y_PR / 100),
      RIGHT_EDGE(sqrt(width * width + height * height) * RIGHT_EDGE_PR / 100) {

  xdir = 1;
  ydir = -1;

  image.load(":/new/Images/ball.png");

  rect = image.rect();
  resetState();
}

Ball::~Ball() {}

void Ball::autoMove() {

  rect.translate(xdir, ydir);

  if (rect.left() == 0) {
    xdir = 1;
  }

  if (rect.right() == RIGHT_EDGE) {
    xdir = -1;
  }

  if (rect.top() == 0) {
    ydir = 1;
  }
}

void Ball::resetState() { rect.moveTo(INITIAL_X, INITIAL_Y); }

void Ball::setXDir(int x) { xdir = x; }

void Ball::setYDir(int y) { ydir = y; }

int Ball::getXDir() { return xdir; }

int Ball::getYDir() { return ydir; }

QRect Ball::getRect() { return rect; }

QImage &Ball::getImage() { return image; }
