#include "infinityengine.h"
#include "ui_infinityengine.h"
#include <iostream>

InfinityEngine::InfinityEngine(QWidget *parent)
: QMainWindow(parent), ui(new Ui::InfinityEngine)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    int id = QFontDatabase::addApplicationFont(
        ":/fonts/Resources/fonts/ARCADECLASSIC.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    setFont(QFont(family));
    resize(800,600);
    animationTimer12.start(1000./12.);
    animationTimer6.start(1000./6.);
    repaintTimer.start(1000./FPS);
    toGameStart();
}
InfinityEngine::~InfinityEngine(){
      delete ui;
}

GameEngine::GameEngine(QWidget *parent)
    : QWidget(parent) {
setFocusPolicy(Qt::StrongFocus);
resize(parent->size());
  frame == FrameType::StartFrame;
  SetStartGameSettings();
}
GameEngine::~GameEngine() {
  delete mainCharactor;
  delete levelMap;
  for (size_t i = 0; i < ActorsArr.size(); ++i)
    delete ActorsArr[i];


}
void GameEngine::SetStartGameSettings() {

  // set font

  // set timers


  // connect timers


  // set map
  MapFactory factory;
  MapImage = QImage(":/maps/Resources/maps/Map1.png");
  levelMap = factory(MapImage);
  levelMapToRectArr();
  // set start weapon
  weapon = weaponFactory(WeaponType::pistol);
  // spawn mainCharactor
  mainCharactor =
      new Charactor(Ray(70, 100, 1, 0), this->width(), 30. / 180. * M_PI);
  // set mapSize
  mapViewWidth = CellSize * levelMap->width;
  mapViewHeight = CellSize * levelMap->height;
  // TODO
  // add Actors;
  addActors();
}
void GameEngine::addActors() {
  AnimationFactory factory;
  QImage StaticSpriteMap(":/maps/Resources/maps/StaticSpriteMap.png");
  QImage BuffesSpriteMap();
  QImage MobSpiteMap(":/maps/Resources/maps/MobsSpriteMap.png");
  for(int i=0;i<StaticSpriteMap.width();++i)
  {
      for(int j=0;j<StaticSpriteMap.height();++j){
          int alpha=qrand();
          //add static sprites
         if(StaticSpriteMap.pixel(i,j)==QColor::fromRgb(187,222,251).rgb()){
             QPointF Pos=QRectF(i*CellSize,j*CellSize,CellSize,CellSize).center();
             ActorsArr.push_back(new Actor(factory(SpriteType::Knight),Pos.x(),Pos.y()));
         }
         if(StaticSpriteMap.pixel(i,j)==QColor::fromRgb(117,117,117).rgb()){
             QPointF Pos=QRectF(i*CellSize,j*CellSize,CellSize,CellSize).center();
             ActorsArr.push_back(new Actor(factory(SpriteType::pillar),Pos.x(),Pos.y()));
         }
         //add bufs
         //add mobs
         if(QColor::fromRgb(MobSpiteMap.pixel(i,j)).red()!=0)
             qDebug() << QColor::fromRgb(MobSpiteMap.pixel(i,j)).red() << ' ' <<
                         QColor::fromRgb(MobSpiteMap.pixel(i,j)).green() << ' ' <<
                         QColor::fromRgb(MobSpiteMap.pixel(i,j)).blue() ;
         if(MobSpiteMap.pixel(i,j)==QColor::fromRgb(244,67,54).rgb()){

             QPointF Pos=QRectF(i*CellSize,j*CellSize,CellSize,CellSize).center();

             ActorsArr.push_back(new Actor(factory(SpriteType::zombe),Pos.x(),Pos.y(),(alpha%2)*0.002,(1-alpha%2)*0.002,Movement::Mobile,Colision::Nothing,100,20,Death::Mortal,100));

         }
         if(MobSpiteMap.pixel(i,j)==QColor::fromRgb(233,30,99).rgb()){

             QPointF Pos=QRectF(i*CellSize,j*CellSize,CellSize,CellSize).center();

             ActorsArr.push_back(new Actor(factory(SpriteType::DoomHead),Pos.x(),Pos.y(),(alpha%2)*0.001,(1-alpha%2)*0.001,Movement::Mobile,Colision::Nothing,100,25,Death::Mortal,300));
         }

      }
  }
 // ActorsArr.push_back(new Actor(factory(SpriteType::DoomHead),100,100,0.001,0,Movement::Mobile,Colision::Nothing,100,20,Death::Mortal,400));

}
void GameEngine::nextTexture() {

  weapon.nextAnimation();
  for (size_t i = 0; i < ActorsArr.size(); ++i)
    ActorsArr[i]->nextTexture();
}
void GameEngine::readyToAttack() {
  for (size_t i = 0; i < ActorsArr.size(); ++i)
    ActorsArr[i]->setReadyToAttack(true);
}
void GameEngine::showEvent(QShowEvent *) {  }
void GameEngine::paintCrosshair(QPainter &ptr) {
  ptr.setPen(Qt::red);
  ptr.drawEllipse(this->width() / 2, this->height() / 2, CrosshairRadius,
                  CrosshairRadius);
}
void GameEngine::keyPressEvent(QKeyEvent *event) {
    nowKeyStatus.KeyPressedNum++;

  if (event->key() == Qt::Key_Left) {

    nowKeyStatus.Left = true;
    nowKeyStatus.KeyPressedNum++;
  }
  if (event->key() == Qt::Key_Right) {

    nowKeyStatus.Right = true;
    nowKeyStatus.KeyPressedNum++;
  }
  if (event->key() == Qt::Key_Up) {

    nowKeyStatus.Up = true;
    nowKeyStatus.KeyPressedNum++;
  }
  if (event->key() == Qt::Key_Down) {

    nowKeyStatus.Down = true;
    nowKeyStatus.KeyPressedNum++;
  }
  if (event->key() == Qt::Key_Space) {
    nowKeyStatus.Space = true;
    nowKeyStatus.KeyPressedNum++;
    // Actor(factory(SpriteType::greenlight)," <<
    // mainCharactor->getCentralRay().getStartPoint().x() << "," <<
    // mainCharactor->getCentralRay().getStartPoint().y() << "));";
  }
  if (event->key() == Qt::Key_1) {

    nowKeyStatus.Key_1 = true;
    nowKeyStatus.KeyPressedNum++;
  }
  if (event->key() == Qt::Key_2) {

    nowKeyStatus.Key_2 = true;
    nowKeyStatus.KeyPressedNum++;
  }
  if (event->key() == Qt::Key_3) {

    nowKeyStatus.Key_3 = true;
    nowKeyStatus.KeyPressedNum++;
  }
}
void GameEngine::keyReleaseEvent(QKeyEvent *event) {
    nowKeyStatus.KeyPressedNum--;
  if (event->key() == Qt::Key_Left) {
    nowKeyStatus.Left = false;
    nowKeyStatus.KeyPressedNum--;
  }
  if (event->key() == Qt::Key_Right) {
    nowKeyStatus.Right = false;
    nowKeyStatus.KeyPressedNum--;
  }
  if (event->key() == Qt::Key_Up) {
    nowKeyStatus.Up = false;
    nowKeyStatus.KeyPressedNum--;
  }
  if (event->key() == Qt::Key_Down) {
    nowKeyStatus.Down = false;
    nowKeyStatus.KeyPressedNum--;
  }
  if (event->key() == Qt::Key_Space) {
    nowKeyStatus.Space = false;
    nowKeyStatus.KeyPressedNum--;
  }
  if (event->key() == Qt::Key_1) {

    nowKeyStatus.Key_1 = false;
    nowKeyStatus.KeyPressedNum--;
  }
  if (event->key() == Qt::Key_2) {

    nowKeyStatus.Key_2 = false;
    nowKeyStatus.KeyPressedNum--;
  }
  if (event->key() == Qt::Key_3) {

    nowKeyStatus.Key_3 = false;
    nowKeyStatus.KeyPressedNum--;
  }
}
void GameEngine::keyEvent() {
  if (frame == FrameType::GameFrame) {
//      if(mainCharactor->getHP()<0){
//          emit GameOver();
//          //TODO
//          frame=FrameType::DieFrame;
//      }
    if (nowKeyStatus.Left)
      mainCharactor->leftRotation();
    if (nowKeyStatus.Right)
      mainCharactor->rightRotation();
    if (nowKeyStatus.Up)
      mainCharactor->Forward();
    if (nowKeyStatus.Down)
      mainCharactor->Backward();
    if (nowKeyStatus.Space) {
      weapon.startAnimation();
      //        AnimationFactory factory;
      //        ActorsArr.push_back(new
      //        Actor(factory(SpriteType::patron),mainCharactor->getCentralRay().getStartPoint().x(),
      //                                      mainCharactor->getCentralRay().getStartPoint().y(),
      //                                      mainCharactor->getCentralRay().getDirection().normalized().x()/10,
      //                                      mainCharactor->getCentralRay().getDirection().normalized().y()/10,
      //                                      Movement::Mobile,
      //                                      Colision::Destroy,
      //                                      1,
      //                                      5,
      //                                      Death::Mortal
      //                                      ));
    }
    if (nowKeyStatus.Key_1) {
      weapon = weaponFactory(WeaponType::knife);
    }
    if (nowKeyStatus.Key_2) {
      weapon = weaponFactory(WeaponType::pistol);
    }
    if (nowKeyStatus.Key_3) {
      weapon = weaponFactory(WeaponType::rifle);
    }
  }  
  if(frame==FrameType::StartFrame)
    {
        if(nowKeyStatus.KeyPressedNum>0)
        {
            emit StartGame();
            frame=FrameType::GameFrame;
        }
    }
    if(frame==FrameType::DieFrame || frame==FrameType::EndFrame)
    {
        if(nowKeyStatus.KeyPressedNum>0)
            exit(0);
    }
}
void GameEngine::paintWeapon(QPainter &ptr) {
  ptr.drawImage(this->width() / 2. - WeaponWidth / 2.,
                this->height() - WeaponHeight,
                weapon.getTexture().scaled(WeaponWidth, WeaponHeight));
}
void GameEngine::paintUI(QPainter &ptr) {
  paintCrosshair(ptr);
  paintWeapon(ptr);
  paintHP(ptr);
}

void GameEngine::paintGameFrame(QPainter &ptr) {

  mainCharactor->calculateEndPoints(rectArr, mapViewWidth, mapViewHeight);
  paint3D(ptr);
  paint2D(ptr);
  paintUI(ptr);
}
void GameEngine::paintHP(QPainter &ptr) {
    if(mainCharactor->getHP()<0)
        emit GameOver();
  ptr.drawImage(20, 550, QImage(":/UI/Resources/UI/HPLogo.png").scaled(50, 50));
  ptr.setFont(QFont(ptr.font().family(), 20));
  ptr.setPen(Qt::red);
  ptr.drawText(90, 550, 100, 100, 0, QString::number(mainCharactor->getHP()));
}

void GameEngine::cheackForEnd()
{
    for(size_t i=0;i<ActorsArr.size();++i)
        if(ActorsArr[i]->getTextureIndex1()!=2 && ActorsArr[i]->getDeathType()==Death::Mortal)
            return;
    emit EndGame();
}
void GameEngine::levelMapToRectArr() {
  double x0 = 0, y0 = 0;
  rectArr.resize(levelMap->wallMap.size());
  for (size_t i = 0; i < levelMap->wallMap.size(); ++i) {
    x0 = this->pos().x();
    for (size_t j = 0; j < levelMap->wallMap[i].size(); ++j) {
      if (levelMap->wallMap[i][j] == '#')
        rectArr[i].push_back(QRectF(x0, y0, CellSize, CellSize));
      x0 += CellSize;
    }
    y0 += CellSize;
  }
}
void GameEngine::recalculateIntarface() {

}
void GameEngine::paintEvent(QPaintEvent *) {
    cheackForEnd();
  keyEvent();
  QPainter ptr3D(this);
  paintGameFrame(ptr3D);

}
void GameEngine::paintFloorAndCeil(QPainter &ptr,
                                       std::vector<Ray> &rayArr) {
  for (size_t i = 0; i < rayArr.size(); ++i) {
    ptr.setPen(QColor::fromRgb(112, 112, 112));
    ptr.drawLine(i, this->height() * 1. / 2., i, this->height());
    ptr.setPen(QColor::fromRgb(56, 56, 56));
    ptr.drawLine(i, 0, i, this->height() * 1. / 2.);
  }
}
void GameEngine::paintWalls(QPainter &ptr, std::vector<Ray> &rayArr) {
  for (size_t i = 0; i < rayArr.size(); ++i) {
    double dist =
        QLineF(rayArr[i].getStartPoint(), rayArr[i].getEndPoint()).length();
    double bCos = QVector2D::dotProduct(
        rayArr[i].getDirection().normalized(),
        mainCharactor->getCentralRay().getDirection().normalized());
    dist *= bCos;
    double sHeight = 64 * 312.5;
    double nHeight = sHeight / (dist);
    double nHeighthp = nHeight / 2;
    double dxP =
        ((uint)rayArr[i].getEndPoint().y() % (uint)CellSize) / CellSize;
    double dyP =
        ((uint)rayArr[i].getEndPoint().x() % (uint)CellSize) / CellSize;
    double dxm = std::min(dxP, 1 - dxP);
    double dym = std::min(dyP, 1 - dyP);
    double deltaP;
    QColor textureType =
        levelMap->textureMap[uint((rayArr[i].getEndPoint().y()) / CellSize)]
                            [uint(((rayArr[i].getEndPoint().x()) / CellSize))];
    if(levelMap->wallMap[uint((rayArr[i].getEndPoint().y()) / CellSize)]
            [uint(((rayArr[i].getEndPoint().x()) / CellSize))]!='#')
    {
        textureType =levelMap->textureMap[uint((rayArr[i].getEndPoint().y()+rayArr[i].getDirection().normalized().y()/10.) / CellSize)]
                                    [uint(((rayArr[i].getEndPoint().x()+rayArr[i].getDirection().normalized().x()/10.) / CellSize))];
    }
    WallTextureFactory factory;
    if (dym < dxm) {
      deltaP = dxP;
      WallTexture = factory(textureType, 0);
    } else {
      deltaP = dyP;
      WallTexture = factory(textureType, 1);
    }

    ptr.drawImage(
        i, (this->height() * 1. / 2. - nHeighthp),
        WallTexture
            .copy(WallTexture.width() * deltaP, 0, 1, WallTexture.height())
            .scaled(1, 2 * nHeight));
  }
}
void GameEngine::paintSprites(QPainter &ptr, std::vector<Ray> &rayArr) {
  for (size_t i = 0; i < ActorsArr.size(); ++i)
    ActorsArr[i]->setIsActivated(true);
  QPointF ActorPos = mainCharactor->getCentralRay().getStartPoint();
  std::sort(ActorsArr.begin(), ActorsArr.end(),
            [ActorPos](Actor *&a, Actor *&b) {
              return QLineF(a->getPosition(), ActorPos).length() >=
                     QLineF(b->getPosition(), ActorPos).length();
            });
  for (size_t i = 0; i < rayArr.size(); ++i) {

    double sHeight = 64 * 312.5;


    for (size_t j = 0; j < ActorsArr.size(); ++j) {

      Sprite sprite(ActorsArr[j]->getSprite(
          mainCharactor->getCentralRay().getStartPoint(), rectArr, width(),
          height()));
      if (sprite.Position == QPointF(-1, -1))
        continue;
      double dist = QLineF(mainCharactor->getCentralRay().getStartPoint(),
                           sprite.Position)
                        .length();
      if (dist >
          QLineF(rayArr[i].getStartPoint(), rayArr[i].getEndPoint()).length() || dist<25)
          continue;
      QVector2D SpriteDir(
          sprite.Position.x() -
              mainCharactor->getCentralRay().getStartPoint().x(),
          sprite.Position.y() -
              mainCharactor->getCentralRay().getStartPoint().y());
      SpriteDir.normalize();
      rayArr[i].setDirection(rayArr[i].getDirection().normalized());
      double centralCos = acos(
          SpriteDir.x() * mainCharactor->getCentralRay().getDirection().x() +
          SpriteDir.y() * mainCharactor->getCentralRay().getDirection().y());
      if (centralCos > 15. / 180. * M_PI)
        continue;
      double localCos = SpriteDir.x() * rayArr[i].getDirection().x() +
                        SpriteDir.y() * rayArr[i].getDirection().y();
      double localSin = SpriteDir.x() * rayArr[i].getDirection().y() -
                        SpriteDir.y() * rayArr[i].getDirection().x();
      double localTan = localSin / localCos;
      int t = dist * localTan;
      double nHeight = sHeight / dist;
      nHeight /= 2.;
      t *= 2;
      if (abs(t) <= sprite.Texture_size) {
        t += sprite.Texture_size / 2.;
        if (fabs(i - rayArr.size() / 2.) < CrosshairRadius)
          if (abs(32 - t) < CrosshairRadius) {
            if (ActorsArr[j]->getDeathType() == Death::Mortal &&
                nowKeyStatus.Space && ActorsArr[j]->getIsActivated() &&
                dist <= weapon.getFigthDistanse() &&
                weapon.getTextureIndex() == 1 && ActorsArr[j]->getHP() > 0) {
              ActorsArr[j]->addHP(-weapon.getDamage());
              ActorsArr[j]->setIsActivated(false);
            }
            if (dist <= ActorsArr[j]->getDamageDistance() &&
                ActorsArr[j]->getReadyToAttack()) {
              ActorsArr[j]->setReadyToAttack(false);

              if (ActorsArr[j]->getTextureIndex1() == 0 &&
                  ActorsArr[j]->getHP() > 0 && dist<ActorsArr[j]->getViewDistance()) {
                ActorsArr[j]->setTextureIndex1(1);
                ActorsArr[j]->setTextureIndex2(0);
                ActorsArr[j]->setTextureIndex3(0);
              }
              if (ActorsArr[j]->getTextureIndex1() == 1 &&
                  ActorsArr[j]->getTextureIndex3() == 0) {
                mainCharactor->setHP(mainCharactor->getHP() -
                                     ActorsArr[j]->getDamage());
              }
            }
          }

        ptr.drawImage(i, (this->height() * 1. / 2. - nHeight),
                      sprite.Texture->copy(t, 0, 1, sprite.Texture->height())
                          .scaled(1, 4 * nHeight));
      }
    }
  }
}

void GameEngine::paint3D(QPainter &ptr) {
  std::vector<Ray> rayArr = mainCharactor->getRayArr();
  paintFloorAndCeil(ptr, rayArr);
  paintWalls(ptr, rayArr);
  paintSprites(ptr, rayArr);
}
void GameEngine::paintLevelMap(QPainter &ptr) {
  ptr.setPen(Qt::black);
  ptr.setBrush(QBrush(Qt::black));
  for (size_t i = 0; i < rectArr.size(); ++i)
    for (size_t j = 0; j < rectArr[i].size(); ++j)
      ptr.drawRect(rectArr[i][j]);
}
void GameEngine::repaintEvent() {
  this->repaint();
  recalculateIntarface();
}
void GameEngine::paint2D(QPainter &ptr) {
   ptr.setClipRect(10, 10, 100, 100);
  MapDelta.setX(miniMapWidth / 2 -
                mainCharactor->getCentralRay().getStartPoint().x() /
                    MapDeltaCof);
  MapDelta.setY(miniMapHeight / 2 -
                mainCharactor->getCentralRay().getStartPoint().y() /
                    MapDeltaCof);

  paintlevelMap(ptr);
  paintMainCharactor(ptr);
   ptr.setClipRect(this->rect());
}

void GameEngine::paintlevelMap(QPainter &ptr) {
  QRect ImageRect = QRect(0, 0, mapViewWidth, mapViewHeight);
  ImageRect.setTop(ImageRect.top() / MapDeltaCof + MapDelta.y());
  ImageRect.setBottom(ImageRect.bottom() / MapDeltaCof + MapDelta.y());
  ImageRect.setLeft(ImageRect.left() / MapDeltaCof + MapDelta.x());
  ImageRect.setRight(ImageRect.right() / MapDeltaCof + MapDelta.x());
  ptr.drawImage(ImageRect, MapImage.scaled(mapViewWidth / MapDeltaCof,
                                           mapViewHeight / MapDeltaCof));
}
void GameEngine::paintMainCharactor(QPainter &ptr) {
  ptr.setPen(Qt::blue);
  for (size_t i = 0; i < mainCharactor->getRayArr().size(); ++i) {
    int x0 = mainCharactor->getRayArr()[i].getStartPoint().x() / MapDeltaCof +
             MapDelta.x();
    int y0 = mainCharactor->getRayArr()[i].getStartPoint().y() / MapDeltaCof +
             MapDelta.y();
    int x1 = mainCharactor->getRayArr()[i].getEndPoint().x() / MapDeltaCof +
             MapDelta.x();
    int y1 = mainCharactor->getRayArr()[i].getEndPoint().y() / MapDeltaCof +
             MapDelta.y();
    ptr.drawLine(x0, y0, x1, y1);
  }
  ptr.setPen(Qt::red);
  int x0 = mainCharactor->getCentralRay().getStartPoint().x() / MapDeltaCof +
           MapDelta.x();
  int y0 = mainCharactor->getCentralRay().getStartPoint().y() / MapDeltaCof +
           MapDelta.y();
  int x1 = mainCharactor->getCentralRay().getEndPoint().x() / MapDeltaCof +
           MapDelta.x();
  int y1 = mainCharactor->getCentralRay().getEndPoint().y() / MapDeltaCof +
           MapDelta.y();
  ptr.drawLine(x0, y0, x1, y1);
  ptr.setPen(Qt::green);
  for (size_t i = 0; i < mainCharactor->getRayArr().size(); ++i) {
    ptr.drawPoint(
        mainCharactor->getRayArr()[i].getEndPoint().x() / MapDeltaCof +
            MapDelta.x(),
        mainCharactor->getRayArr()[i].getEndPoint().y() / MapDeltaCof +
            MapDelta.y());
  }
}

Weapon StartMenuEngine::getFrameTexture() const
{
    return FrameTexture;
}

void StartMenuEngine::setFrameTexture(const Weapon &value)
{
    FrameTexture = value;
}
Weapon DieMenuEngine::getFrameTexture() const
{
    return FrameTexture;
}

void DieMenuEngine::setFrameTexture(const Weapon &value)
{
    FrameTexture = value;
}

Weapon EndMenuEngine::getFrameTexture() const
{
    return FrameTexture;
}

void EndMenuEngine::setFrameTexture(const Weapon &value)
{
    FrameTexture = value;
}
