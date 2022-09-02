#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include "basenavigator.h"
#include "screensfactory.h"
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class TestWindow;
}
QT_END_NAMESPACE

class TestWindow : public QMainWindow {
  Q_OBJECT

public:
  TestWindow(QWidget *parent = nullptr);
  ~TestWindow();

private:
  Ui::TestWindow *ui;
  QStackedWidget *container;
  ScreensFactory *factory;
  BaseNavigator *navigator;
};
#endif // TESTWINDOW_H
