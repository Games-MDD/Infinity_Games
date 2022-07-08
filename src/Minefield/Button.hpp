#ifndef BUTTON_H
#define BUTTON_H

#include <QMouseEvent>
#include <QPushButton>

class Button : public QPushButton {
  Q_OBJECT

public:
  explicit Button(int v, int x, int y, QWidget *parent = 0) : QPushButton(parent), val(v), xCord(x), yCord(y) {}

private slots:
  void mousePressEvent(QMouseEvent *e);
  void onLeftClicked();
  void onRightClicked();

private:
  int val, xCord, yCord; // значение кнопки, координаты в массиве
  bool isFlagged = false;
  bool isOpen = false;

signals:
  void flag();

  friend class MainWindow;
};

#endif // BUTTON_H
