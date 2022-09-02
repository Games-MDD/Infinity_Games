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

      static const int WINDOW_WIDTH = 500;
      static const int WINDOW_HEIGHT = 500;
      static const int DOT_SIZE = 10;
      static const int NUMBER_OF_DOTS = 2500;
      static const int RAND_POS_CONST = 50;
      static const int DELAY = 70;

      int timerId;
      int dots;
      int appleX;
      int appleY;

      int score = 0;

      int x[NUMBER_OF_DOTS];
      int y[NUMBER_OF_DOTS];

      bool leftDir;
      bool rightDir;
      bool upDir;
      bool downDir;
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
      void HelpMessage();
      void clearResults();
};

#endif // SANKE_H
