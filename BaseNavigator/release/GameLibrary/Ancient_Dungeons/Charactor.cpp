#include "Charactor.h"
#include <QtDebug>
Charactor::Charactor(const Charactor &actor)
    : ViewAngle(actor.ViewAngle), RayNum(actor.RayNum) {
  CentralRay = actor.CentralRay;
  RayArr = actor.RayArr;
}
Charactor::Charactor(Ray centralRay, qint32 rayNum, double angle = 110)
    : ViewAngle(angle), RayNum(rayNum) {
  CentralRay = centralRay;
  RayArr.push_back(CentralRay);
  RayArr.back().Rotate(-ViewAngle / 2);
  for (qint32 i = 0; i < RayNum - 1; ++i) {
    RayArr.push_back(RayArr.back());
    RayArr.back().Rotate(ViewAngle / RayNum);
  }
}
double Charactor::getviewDistance() { return ViewDistance; }
QPointF Charactor::calculateEndPoints(QLineF &line, Ray &ray) {
  if ((line.dx() == 0 && fabs(ray.getDirection().x()) <= 1e-6) ||
      (line.dy() == 0 && fabs(ray.getDirection().y()) <= 1e-6)) {
    return QPointF(-1, -1);
  }

  if (line.dx() == 0) {
    double t = (line.x1() - ray.getStartPoint().x()) / ray.getDirection().x();
    if (t < 0) {
      return QPointF(-1, -1);
    }
    double x = line.x1();
    double y = (ray.getStartPoint().y() + ray.getDirection().y() * t);
    if (y <= std::fmax(line.y1(), line.y2()) &&
        y >= std::fmin(line.y1(), line.y2())) {
      return QPointF(x, y);
    } else {
      return QPointF(-1, -1);
    }
  }
  double t = (line.y1() - ray.getStartPoint().y()) / ray.getDirection().y();
  if (t < 0) {
    return QPointF(-1, -1);
  }
  double y = line.y1();
  double x = (ray.getStartPoint().x() + ray.getDirection().x() * t);
  if (x <= std::fmax(line.x1(), line.x2()) &&
      x >= std::fmin(line.x1(), line.x2())) {
    return QPointF(x, y);
  } else {
    return QPointF(-1, -1);
  }
}

std::vector<QPointF> Charactor::calculateEndPoints(QRectF &rect, Ray &ray) {
  std::vector<QPointF> pointArr;
  pointArr.reserve(4);
  QLineF line = QLineF(rect.topLeft(), rect.topRight());
  pointArr.push_back(calculateEndPoints(line, ray));
  line = QLineF(rect.bottomLeft(), rect.bottomRight());
  pointArr.push_back(calculateEndPoints(line, ray));
  line = QLineF(rect.topLeft(), rect.bottomLeft());
  pointArr.push_back(calculateEndPoints(line, ray));
  line = QLineF(rect.topRight(), rect.bottomRight());
  pointArr.push_back(calculateEndPoints(line, ray));
  return pointArr;
}
QPointF
Charactor::calculateEndPoints(const std::vector<std::vector<QRectF>> &rectArr,
                          qint32 width, qint32 height, Ray &ray) {
  std::vector<std::vector<QPointF>> pointArr;
  QRectF rectCopy;
  pointArr.reserve(rectArr.size());
  for (size_t i = 0; i < rectArr.size(); ++i) {
    for (size_t j = 0; j < rectArr[i].size(); ++j) {
      rectCopy = rectArr[i][j];
      pointArr.push_back(calculateEndPoints(rectCopy, ray));
    }
  }
  rectCopy = QRectF(0, 0, width, height);
  pointArr.push_back(calculateEndPoints(rectCopy, ray));
  QPointF answer = QPointF(-1, -1);
  for (size_t i = 0; i < pointArr.size(); ++i)
    for (size_t j = 0; j < pointArr[i].size(); ++j) {
      if (pointArr[i][j] != QPointF(-1, -1)) {
        if (QLineF(ray.getStartPoint(), answer).length() >
                QLineF(ray.getStartPoint(), pointArr[i][j]).length() ||
            answer == QPointF(-1, -1)) {
          answer = pointArr[i][j];
        }
      }
    }

  return answer;
}
void Charactor::calculateEndPoints(const std::vector<std::vector<QRectF>> &rectArr,
                               qint32 width, qint32 height) {
  CentralRay.setEndPoint(
      calculateEndPoints(rectArr, width, height, CentralRay));
  for (size_t i = 0; i < RayArr.size(); ++i) {
    RayArr[i].setEndPoint(
        calculateEndPoints(rectArr, width, height, RayArr[i]));
  }
}
QPointF Charactor::calculateEndPoints(const std::vector<QString> &levelMap,
                                  qint32 width, qint32 height, Ray &ray) {
  double dwidth = width / levelMap[0].length();
  double dheight = height / levelMap.size();
  double x = ray.getStartPoint().x();
  double y = ray.getStartPoint().y();
  QVector2D Dir = ray.getDirection().normalized();

  while (x < width && y < height) {

    x += Dir.x();
    y += Dir.y();
    if (int(y / dheight) >= levelMap.size() || int(y / dheight) < 0 ||
        int(x / dwidth) >= levelMap[0].length() || int(x / dwidth) < 0) {
      x -= Dir.x();
      y -= Dir.y();
      break;
    }
    if (levelMap[qint32(y / dheight)][qint32(x / dwidth)] == '#') {
      x -= Dir.x();
      y -= Dir.y();
      break;
    }
  }
  return QPointF(int(x), int(y));
}
void Charactor::calculateEndPoints(const std::vector<QString> &levelMap,
                               qint32 width, qint32 height) {
  CentralRay.setEndPoint(
      calculateEndPoints(levelMap, width, height, CentralRay));
  for (size_t i = 0; i < RayArr.size(); ++i) {
    RayArr[i].setEndPoint(
        calculateEndPoints(levelMap, width, height, RayArr[i]));
  }
}
double Charactor::getHP() const
{
    return HP;
}

void Charactor::setHP(double value)
{
    HP = value;
}

Charactor::Charactor() : Charactor(Ray(0, 0, 1, 0), 0, 60 / 180 * M_PI) {}
void Charactor::leftRotation(const double stepAngle) {
  CentralRay.Rotate(-stepAngle);

  for (qint32 i = 0; i < RayNum; ++i)
    RayArr[i].Rotate(-stepAngle);
}
void Charactor::rightRotation(const double stepAngle) { leftRotation(-stepAngle); }
void Charactor::Forward() {
  CentralRay.setDirection(CentralRay.getDirection().normalized());
  QPointF newPosition;
  double mul = 10;
  double mul2 = 1;
  CentralRay.setDirection(CentralRay.getDirection().normalized());
  newPosition.setX(CentralRay.getStartPoint().x() +
                   mul * CentralRay.getDirection().x());
  newPosition.setY(CentralRay.getStartPoint().y() +
                   mul * CentralRay.getDirection().y());
  double dtoEndx, dtoEndy, dtoNewx, dtoNewy;
  dtoEndx =
      qFabs(CentralRay.getStartPoint().x() - CentralRay.getEndPoint().x());
  dtoEndy =
      qFabs(CentralRay.getStartPoint().y() - CentralRay.getEndPoint().y());
  dtoNewx = qFabs(CentralRay.getStartPoint().x() - newPosition.x());
  dtoNewy = qFabs(CentralRay.getStartPoint().y() - newPosition.y());
  double x = CentralRay.getStartPoint().x(), y = CentralRay.getStartPoint().y();
  if (dtoEndx * mul2 >= dtoNewx) {
    x = newPosition.x();
  }
  if (dtoEndy * mul2 >= dtoNewy) {
    y = newPosition.y();
  }
  CentralRay.setStartPoint(QPointF(x, y));
  for (qint32 i = 0; i < RayNum; ++i)
    RayArr[i].setStartPoint(CentralRay.getStartPoint());
}
// TODO make end revers direction ray
void Charactor::Backward() {
  CentralRay.setDirection(CentralRay.getDirection().normalized());
  QPointF newPosition;
  double mul = 10;
  newPosition.setX(CentralRay.getStartPoint().x() -
                   mul * CentralRay.getDirection().x());
  newPosition.setY(CentralRay.getStartPoint().y() -
                   mul * CentralRay.getDirection().y());
  //  double dtoEndx,dtoEndy,dtoNewx,dtoNewy;
  //  dtoEndx=qAbs(Geometry.getPosition().x()-EndPoint.x());
  //  dtoEndy=qAbs(Geometry.getPosition().y()-EndPoint.y());
  //  dtoNewx=qAbs(Geometry.getPosition().x()-newPosition.x());
  //  dtoNewy=qAbs(Geometry.getPosition().y()-newPosition.y());
  //  if(dtoEndx>=dtoNewx)
  //      Geometry.setPosition(QPoint(newPosition.x(),Geometry.getPosition().y()));
  //  if(dtoEndy>=dtoNewy)
  //      Geometry.setPosition(QPoint(Geometry.getPosition().x(),newPosition.y()));
  CentralRay.setStartPoint(newPosition);
  for (qint32 i = 0; i < RayNum; ++i)
    RayArr[i].setStartPoint(CentralRay.getStartPoint());
}
Ray Charactor::getCentralRay() { return CentralRay; }
double Charactor::getViewAngle() { return ViewAngle; }
qint32 Charactor::getRayNum() { return RayNum; }
std::vector<Ray> Charactor::getRayArr() { return RayArr; }
void Charactor::setGeometry(Ray geometry) { CentralRay = geometry; }
