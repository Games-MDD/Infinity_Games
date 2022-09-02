#ifndef ACTOR_H
#define ACTOR_H
#include "ray.h"
#include <QLineF>
#include <QObject>
#include <QRectF>
#include <QVector2D>
#include <QtMath>
#include <vector>
class Charactor {
private:
  Ray CentralRay;
  const double ViewAngle = 110;
  const qint32 RayNum;
  std::vector<Ray> RayArr;
  const double ViewDistance = 100;
  const double MaxRayLength = 10;
  double HP=100;
public:
  Charactor();
  Charactor(const Charactor &);
  Charactor(Ray, qint32, double);
  double getviewDistance();
  QPointF calculateEndPoints(const std::vector<QString> &, qint32, qint32,
                             Ray &);
  QPointF calculateEndPoints(QLineF &, Ray &);
  std::vector<QPointF> calculateEndPoints(QRectF &, Ray &);
  QPointF calculateEndPoints(const std::vector<std::vector<QRectF>> &, qint32,
                             qint32, Ray &);
  void calculateEndPoints(const std::vector<std::vector<QRectF>> &, qint32,
                             qint32);
  void calculateEndPoints(const std::vector<QString> &, qint32, qint32);
  Ray getCentralRay();
  double getViewAngle();
  qint32 getRayNum();
  std::vector<Ray> getRayArr();
  void setGeometry(const Ray geometry);
  double getHP() const;
  void setHP(double value);

public slots:

  void leftRotation(const double stepAngle = 3. / 180. * M_PI);
  void rightRotation(const double stepAngle = 3. / 180. * M_PI);
  void Forward();
  void Backward();
};

#endif // ACTOR_H
