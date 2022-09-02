#ifndef STATICACTOR_H
#define STATICACTOR_H
#include <Sprite.h>
#include <ray.h>
enum Movement { Static, Mobile };
enum Colision { Destroy, Nothing };
enum Death { Mortal, Immortal };

class Actor {
private:
  bool destroed;
  double HP;
  double Damage;
  Movement MovementType;
  Colision ColisionType;
  Death DeathType;
  Ray mainRay;
  double DamageDistance;
  const double ViewDistance=500;
  bool isActivated = true;
  int textureIndex1 = 0, textureIndex2 = 0, textureIndex3 = 0;
  bool ReadyToAttack=false;
  std::vector<std::vector<std::vector<QImage>>> FramesArr;

public:
  virtual ~Actor();
  Actor(std::vector<std::vector<std::vector<QImage>>> frameArr, double x,
        double y, double dx = 0, double dy = 0, Movement movementType = Static,
        Colision colisionType = Nothing, double hp = 1, double damage = 0,
        Death deathType = Death::Immortal,double damageDistance=100);
  virtual void setPosition(QPointF position) {
    mainRay.setStartPoint(position);
  }
  void nextTexture();
  virtual QPointF getPosition() { return mainRay.getStartPoint(); }
  virtual Sprite getSprite(QPointF, std::vector<std::vector<QRectF>>, int, int);
  bool isDestroed() { return destroed; }
  void Destroy() { destroed = true; }

  Death getDeathType() const;
  bool getIsActivated() const;
  void setIsActivated(bool value);
  void addHP(double damage) { HP += damage; }
  double getHP() const;
  void setHP(double value);
  int getTextureIndex3() const;
  double getDamageDistance() const;
  double getDamage() const;
  int getTextureIndex1() const;
  void setTextureIndex1(int value);
  int getTextureIndex2() const;
  void setTextureIndex2(int value);
  void setTextureIndex3(int value);
  bool getReadyToAttack() const;
  void setReadyToAttack(bool value);
  void setDamageDistance(double value);
  double getViewDistance() const;
};

#endif // STATICACTOR_H
