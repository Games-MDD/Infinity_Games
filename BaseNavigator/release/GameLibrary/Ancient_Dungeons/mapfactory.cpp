#include "mapfactory.h"
#include <QtDebug>
#include<iostream>
Map *MapFactory::operator()(QImage img) {
  Map *answer = new Map;
  // set width and height
  answer->width = img.height();
  answer->height = img.width();
  answer->wallMap.resize(answer->width, std::vector<uint>(answer->height));
  answer->textureMap.resize(answer->width, std::vector<QColor>(answer->height));
  answer->ceilMap.resize(answer->width, std::vector<uint>(answer->height));
  answer->floorMap.resize(answer->width, std::vector<uint>(answer->height));
  // set texture map
  for (int x = 0; x < img.width(); ++x) {
    for (int y = 0; y < img.height(); ++y) {
      answer->textureMap[y][x] =  img.pixel(x, y);
    }
  }
  // set wall map
  for (int x = 0; x < img.width(); ++x) {
    for (int y = 0; y < img.height(); ++y) {
      //qDebug() << QColor(img.pixel(x, y));
      if (QColor(img.pixel(x, y)) != QColor(Qt::white))
        answer->wallMap[y][x]  = '#';
      else
        answer->wallMap[y][x]  = '.';
    }
  }

  return answer;
}
