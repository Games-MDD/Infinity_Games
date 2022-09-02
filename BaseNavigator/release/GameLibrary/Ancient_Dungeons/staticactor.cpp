#include "staticactor.h"
Death Actor::getDeathType() const { return DeathType; }

bool Actor::getIsActivated() const { return isActivated; }

void Actor::setIsActivated(bool value) { isActivated = value; }

double Actor::getHP() const { return HP; }

void Actor::setHP(double value) { HP = value; }

int Actor::getTextureIndex3() const { return textureIndex3; }

double Actor::getDamageDistance() const { return DamageDistance; }

double Actor::getDamage() const { return Damage; }

int Actor::getTextureIndex1() const { return textureIndex1; }

void Actor::setTextureIndex1(int value) {
  if (value < FramesArr.size())
    textureIndex1 = value;
}

int Actor::getTextureIndex2() const { return textureIndex2; }

void Actor::setTextureIndex2(int value) {
  if (value < FramesArr[0].size())
    textureIndex2 = value;
}

void Actor::setTextureIndex3(int value) {
  if (value < FramesArr[0][0].size())
    textureIndex3 = value;
}

bool Actor::getReadyToAttack() const { return ReadyToAttack; }

void Actor::setReadyToAttack(bool value) { ReadyToAttack = value; }

void Actor::setDamageDistance(double value)
{
    DamageDistance = value;
}

double Actor::getViewDistance() const
{
    return ViewDistance;
}

Actor::~Actor() {}
Actor::Actor(std::vector<std::vector<std::vector<QImage>>> frameArr, double x,
             double y, double dx, double dy, Movement movementType,
             Colision colisionType, double hp, double damage, Death deathType,
             double damageDistance) {
  FramesArr = frameArr;
  destroed = false;
  mainRay = Ray(x, y, dx, dy);
  MovementType = movementType;
  ColisionType = colisionType;
  HP = hp;
  Damage = damage;
  DeathType = deathType;
  DamageDistance = damageDistance;
}

void Actor::nextTexture() {

  if (textureIndex1 == 2 &&
      textureIndex3 == FramesArr[textureIndex1][textureIndex2].size() - 1)
    return;
  if (textureIndex1 == 1 &&
      textureIndex3 == FramesArr[textureIndex1][textureIndex2].size() - 1)
    textureIndex1 = 0;
  textureIndex3 =
      (textureIndex3 + 1) % FramesArr[textureIndex1][textureIndex2].size();
}
Sprite Actor::getSprite(QPointF CharactorPosition,
                        std::vector<std::vector<QRectF>> RectArr, int width,
                        int heigth) {
  if (QLineF(CharactorPosition,mainRay.getStartPoint()).length()<ViewDistance) {
    mainRay.setDirection(
        QVector2D(CharactorPosition.x() - mainRay.getStartPoint().x(),
                  CharactorPosition.y() - mainRay.getStartPoint().y())
            .normalized());
    mainRay.Scale(0.001);
  }

  if (destroed)
    return Sprite(FramesArr[0][0][0], QPointF(-1, -1));

  if (HP <= 0 && DeathType == Death::Mortal && textureIndex1 != 2) {
    textureIndex1 = 2;
    textureIndex2 = 0;
    textureIndex3 = 0;
  }
  if (textureIndex1 == 0) {
    QVector2D ToEnemy((CharactorPosition.x() - mainRay.getStartPoint().x()),
                      (CharactorPosition.y() - mainRay.getStartPoint().y()));
    ToEnemy.normalize();
    QVector2D DeltaV(mainRay.getDirection().normalized().x() - ToEnemy.x(),
                     mainRay.getDirection().normalized().y() - ToEnemy.y());
    DeltaV.normalize();
    double Fi = atan2(DeltaV.y(), DeltaV.x());
    double FiDag=Fi*180/M_PI;
    textureIndex2 =((int(FiDag)%360+180)/ 45+4) % FramesArr[textureIndex1].size();
  }
  Sprite answer = Sprite(FramesArr[textureIndex1][textureIndex2][textureIndex3],
                         mainRay.getStartPoint());

  if (MovementType == Movement::Mobile && textureIndex1 == 0) {
    mainRay.Move(mainRay.getDirection().x(), mainRay.getDirection().y());
    bool isNear = false;
    if (mainRay.getStartPoint().x() < 0 || mainRay.getStartPoint().y() < 0 ||
        mainRay.getStartPoint().x() >= width ||
        mainRay.getStartPoint().y() >= heigth)
      isNear = false;
    for (size_t i = 0; i < RectArr.size(); ++i)
      for (size_t j = 0; j < RectArr[i].size(); ++j) {
        if (mainRay.getStartPoint().x() >= RectArr[i][j].left() &&
            mainRay.getStartPoint().x() <= RectArr[i][j].right())
          if (mainRay.getStartPoint().y() >= RectArr[i][j].top() &&
              mainRay.getStartPoint().y() <= RectArr[i][j].bottom())
            isNear = true;
      }
    if (isNear)
      if (ColisionType == Colision::Destroy) {
        Destroy();
      } else {
        mainRay.Scale(-1);
      }
  }
  return answer;
}
