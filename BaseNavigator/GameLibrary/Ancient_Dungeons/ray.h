#ifndef RAY_H
#define RAY_H
#include<QVector2D>
#include<QtMath>
#include<QObject>
class Ray
{
private:
    QVector2D Direction;
    QPointF StartPoint;
    QPointF EndPoint;
public:
    Ray();
    Ray(const Ray& ray);
    Ray(QPointF X,QVector2D VX);
    Ray(double x,double y,double vx,double vy);
    void Rotate(double corner);
    void Move(double dx,double dy);
    void Scale(double mul);
    QVector2D getDirection();
    QPointF getStartPoint();
    QPointF getEndPoint();
    void setDirection(QVector2D direction);
    void setStartPoint(QPointF position);
    void setEndPoint(QPointF position);

};

#endif // RAY_H
