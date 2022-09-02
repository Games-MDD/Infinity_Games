#ifndef INFINITYENGINE_H
#define INFINITYENGINE_H

#include <AnimationFactory.h>
#include <Charactor.h>
#include <KeyStatus.h>
#include <QMainWindow>
#include <QTimer>
#include <QtMultimedia/qmediaplayer.h>
#include <QtWidgets>
#include <WeaponFactory.h>
#include <mapfactory.h>
#include <sprite.h>
#include <staticactor.h>
#include <vector>
#include <walltexturefactory.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class InfinityEngine;
}
QT_END_NAMESPACE
enum FrameType { StartFrame, GameFrame, DieFrame, EndFrame };
class InfinityEngine;
class GameEngine : public QWidget {
  Q_OBJECT
private:
  const int Fps = 30;
  QImage WallTexture;

  Weapon weapon;
  WeaponFactory weaponFactory;
  FrameType frame = FrameType::StartFrame;
  Map *levelMap;
  QImage MapImage;
  KeyStatus nowKeyStatus;
  std::vector<std::vector<QRectF>> rectArr;
  QMediaPlayer Player;
  // TODO
  double mapViewWidth, mapViewHeight;
  double miniMapWidth = 100, miniMapHeight = 100;
  double CellSize = 40;
  const int WeaponWidth = 500;
  const int WeaponHeight = 500;
  const double CrosshairRadius = 10;
  QPointF MapDelta;
  double MapDeltaCof = 6;
  Charactor *mainCharactor;
  std::vector<Actor *> ActorsArr;
signals:
  void GameOver();
  void EndGame();
  void StartGame();

public:
  GameEngine(QWidget *parent = nullptr);
  ~GameEngine();
  void SetStartGameSettings();
  void addActors();
  void paintEvent(QPaintEvent *);
  void paintLevelMap(QPainter &);
  void paintUI(QPainter &);
  void paintGameFrame(QPainter &);
  void paintMainCharactor(QPainter &);
  void paintlevelMap(QPainter &ptr);
  void paintCrosshair(QPainter &ptr);
  void paintWeapon(QPainter &);
  void paintHP(QPainter &);
  void cheackForEnd();
  void paintFloorAndCeil(QPainter &, std::vector<Ray> &);
  void recalculateIntarface();
  void paintWalls(QPainter &, std::vector<Ray> &);
  void paintSprites(QPainter &, std::vector<Ray> &);
  void paint3D(QPainter &);
  void paint2D(QPainter &);
  void showEvent(QShowEvent *);
private slots:
  void nextTexture();
  void readyToAttack();
  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);
  void keyEvent();
  void repaintEvent();
  void levelMapToRectArr();
};
class StartMenuEngine : public QWidget {
  Q_OBJECT
private:
  Weapon FrameTexture;

public:
  StartMenuEngine(QWidget *parent = nullptr) : QWidget(parent) {
      setFocusPolicy(Qt::StrongFocus);
    resize(parent->size());
    WeaponFactory weaponFactory;
    setFrameTexture(weaponFactory(WeaponType::startScreen));
  }
  void paintEvent(QPaintEvent *event) {
    QPainter ptr(this);
    ptr.drawImage(
        0, 0, FrameTexture.getTexture().scaled(this->width(), this->height()));
    ptr.setPen(Qt::red);
    ptr.setFont(QFont(ptr.font().family(), 30));
    ptr.drawText(0, 0, this->width(), this->height(),
                 Qt::AlignHCenter | Qt::AlignBottom, "PRESS START");
  }
  void keyPressEvent(QKeyEvent *event) { emit startGame(); }
public slots:
  void nextTexture() {
    FrameTexture.nextAnimation();
    repaint();
  }

public:
  Weapon getFrameTexture() const;
  void setFrameTexture(const Weapon &value);

signals:
  void startGame();
  void exitGame();
};
class DieMenuEngine : public QWidget {
  Q_OBJECT
private:
  Weapon FrameTexture;

public:
  DieMenuEngine(QWidget *parent = nullptr) : QWidget(parent) {
      setFocusPolicy(Qt::StrongFocus);
    resize(parent->size());
    WeaponFactory weaponFactory;
    setFrameTexture(weaponFactory(WeaponType::dieGame));
  }
  void paintEvent(QPaintEvent *event) {
    QPainter ptr(this);
    ptr.drawImage(
        0, 0, FrameTexture.getTexture().scaled(this->width(), this->height()));
    ptr.setPen(Qt::red);
    ptr.setFont(QFont(ptr.font().family(), 30));
    ptr.drawText(0, 0, this->width(), this->height(),
                 Qt::AlignHCenter | Qt::AlignBottom, "PRESS TO RESTART");
  }
  void keyPressEvent(QKeyEvent *event) { emit restartGame(); }
public slots:
  void nextTexture() {
    FrameTexture.nextAnimation();
    repaint();
  }

public:
  Weapon getFrameTexture() const;
  void setFrameTexture(const Weapon &value);

signals:
  void restartGame();
  void exitGame();
};
class EndMenuEngine : public QWidget {
  Q_OBJECT
private:
  Weapon FrameTexture;

public:
  EndMenuEngine(QWidget *parent = nullptr) : QWidget(parent) {
      setFocusPolicy(Qt::StrongFocus);
    resize(parent->size());
    WeaponFactory weaponFactory;
    setFrameTexture(weaponFactory(WeaponType::endGame));
  }
  void paintEvent(QPaintEvent *event) {
    QPainter ptr(this);
    ptr.drawImage(
        0, 0, FrameTexture.getTexture().scaled(this->width(), this->height()));
    ptr.setPen(Qt::red);
    ptr.setFont(QFont(ptr.font().family(), 30));
    ptr.drawText(0, 0, this->width(), this->height(),
                 Qt::AlignHCenter | Qt::AlignBottom, "PRESS START");
  }
  void keyPressEvent(QKeyEvent *event) { emit restartGame(); }
public slots:
  void nextTexture() {
    FrameTexture.nextAnimation();
    repaint();
  }

public:
  Weapon getFrameTexture() const;
  void setFrameTexture(const Weapon &value);

signals:
  void restartGame();
  void exitGame();
};

class InfinityEngine : public QMainWindow {
  Q_OBJECT
private:
  const double FPS=60;
  QTimer repaintTimer;
  QTimer animationTimer12;
  QTimer animationTimer6;
  QTimer animationTimer3;
  GameEngine *gameEngine = nullptr;
  StartMenuEngine *startMenuEngine = nullptr;
  EndMenuEngine *endMenuEngine = nullptr;
  DieMenuEngine *dieMenuEngine = nullptr;
  FrameType frame;
  Ui::InfinityEngine *ui;
public slots:
  void startGame() {
    if (startMenuEngine != nullptr) {
      delete startMenuEngine;
      startMenuEngine = nullptr;
    }
    gameEngine = new GameEngine(this);
    setCentralWidget(gameEngine);
    connect(&animationTimer12, SIGNAL(timeout()), gameEngine,
            SLOT(nextTexture()));
    connect(&animationTimer6, SIGNAL(timeout()), gameEngine,
            SLOT(readyToAttack()));
    connect(gameEngine, SIGNAL(GameOver()), this, SLOT(GameOver()));
    connect(gameEngine, SIGNAL(EndGame()), this, SLOT(EndGame()));
    connect(&repaintTimer, SIGNAL(timeout()), gameEngine, SLOT(repaintEvent()));
  }
  void GameOver() {
    dieMenuEngine = new DieMenuEngine(this);
    connect(&animationTimer12, SIGNAL(timeout()), dieMenuEngine,
            SLOT(nextTexture()));
    connect(dieMenuEngine,SIGNAL(restartGame()),this,SLOT(startGame()));
    setCentralWidget(dieMenuEngine);
  }
  void EndGame() {
//    if (gameEngine != nullptr) {
//      delete gameEngine;
//      gameEngine = nullptr;
//    }
    endMenuEngine = new EndMenuEngine(this);
    connect(&animationTimer12, SIGNAL(timeout()), endMenuEngine,
            SLOT(nextTexture()));
    connect(endMenuEngine,SIGNAL(restartGame()),this,SLOT(startGame()));
    setCentralWidget(endMenuEngine);
  }
  void toGameStart() {
    if (dieMenuEngine != nullptr) {
      delete dieMenuEngine;
      dieMenuEngine = nullptr;
    }
    if (endMenuEngine != nullptr) {
      delete endMenuEngine;
      endMenuEngine = nullptr;
    }
    startMenuEngine = new StartMenuEngine(this);
    connect(&animationTimer12, SIGNAL(timeout()), startMenuEngine,
            SLOT(nextTexture()));
    connect(startMenuEngine,SIGNAL(startGame()),this,SLOT(startGame()));
    setCentralWidget(startMenuEngine);
  }

public:
  InfinityEngine(QWidget *parent = nullptr);
  ~InfinityEngine();
};

#endif // INFINITYENGINE_H
