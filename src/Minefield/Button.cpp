#include "Button.hpp"
#include <QMouseEvent>

void Button::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::RightButton)
    emit onRightClicked();
  else
    emit onLeftClicked();
}

void Button::onLeftClicked() {
  if (!isFlagged)
    emit clicked();
}

void Button::onRightClicked() { emit flag(); }