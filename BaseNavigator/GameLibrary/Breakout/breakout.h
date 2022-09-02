#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "ball.h"
#include "brick.h"
#include "paddle.h"
#include <QKeyEvent>
#include <QWidget>

#include <QApplication>
#include <QPainter>
class Breakout : public QWidget {
public:
  Breakout(QWidget *parent = 0);
  ~Breakout();

protected:
  void paintEvent(QPaintEvent *);
  void timerEvent(QTimerEvent *);
  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);
  void drawObjects(QPainter *);
  void finishGame(QPainter *, QString);
  void moveObjects();
  void startGame();
  void pauseGame();
  void stopGame();
  void victory();
  void checkCollision();

private:
  int x;
  int timerId;
  int N_OF_BRICKS = 100;
  static const int WIDTH_OF_BRICKS_PR = 10;
  static const int HEIGHT_OF_BRICKS_PR = 5;
  static const int DELAY = 10;
  static const int BOTTOM_EDGE_PR = 100;
  const int BOTTOM_EDGE;
  Ball *ball;
  Paddle *paddle;
  QVector<Brick *> bricks;
  bool gameOver;
  bool gameWon;
  bool gameStarted;
  bool paused;
};
#endif // BREAKOUT_H
