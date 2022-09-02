#include "ray.h"
Ray::Ray() {}
Ray::Ray(const Ray &ray) {
  Direction = ray.Direction;
  StartPoint = ray.StartPoint;
  EndPoint=ray.EndPoint;
}
Ray::Ray(QPointF X, QVector2D VX): Ray(X.x(),X.y(),VX.x(),VX.y()) {

}
Ray::Ray(double x, double y, double vx, double vy) {
  StartPoint = QPointF(x, y);
  Direction = QVector2D(vx, vy);
  EndPoint = QPointF(x+vx,y+vy);
}
void Ray::Rotate(double corner) {

  double x = Direction.x();
  double y = Direction.y();
  Direction.setX(x * qCos(corner) - y * qSin(corner));
  Direction.setY(x * qSin(corner) + y * qCos(corner));
}
void Ray::Move(double dx, double dy) {
  StartPoint.setX(StartPoint.x() + dx);
  StartPoint.setY(StartPoint.y() + dy);
}
void Ray::Scale(double mul) {
  Direction.setX(Direction.x() * mul);
  Direction.setY(Direction.y() * mul);
}
QVector2D Ray::getDirection() { return Direction; }
QPointF Ray::getStartPoint() { return StartPoint; }
QPointF Ray::getEndPoint() { return EndPoint; }
void Ray::setDirection(QVector2D direction) { Direction = direction.normalized(); }
void Ray::setStartPoint(QPointF position) { StartPoint = position; }
void Ray::setEndPoint(QPointF position) { EndPoint = position; }
