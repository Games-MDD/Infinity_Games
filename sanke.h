#ifndef SANKE_H
#define SANKE_H

#include <QWidget>
#include <QKeyEvent>
#include <set>

class Snake : public QWidget
{
public:
     Snake(QWidget *parent = nullptr);
     virtual void onPause();
     virtual void onResume();
protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

  private:
      QImage dot;
      QImage head;
      QImage apple;
      QWidget* resWindow;
      std::set <std::pair <int, QString> > results;

      static const int B_WIDTH = 500;
      static const int B_HEIGHT = 500;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 2500;
      static const int RAND_POS = 50;
      static const int DELAY = 70;

      int timerId;
      int dots;
      int apple_x;
      int apple_y;

      int score = 0;

      int x[ALL_DOTS];
      int y[ALL_DOTS];

      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;
      bool inGame;
      bool paused;

      void loadImages();
      void initGame();
      void locateApple();
      void checkApple();
      void checkCollision();
      void move();
      void doDrawing();
      void gameOver(QPainter &);
      void saveRecord(QString aName);
      void showResults();
      void stopGame();
      void loadData();
      void saveData();
};

#endif // SANKE_H
