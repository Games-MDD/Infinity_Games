#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include "basenavigator.h"
#include "screensfactory.h"
QT_BEGIN_NAMESPACE
namespace Ui { class TestWindow; }
QT_END_NAMESPACE

class TestWindow : public QWidget
{
    Q_OBJECT

public:
    TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Ui::TestWindow *ui;
    QStackedWidget* container;
    ScreensFactory* factory;
    BaseNavigator* navigator;
};
#endif // TESTWINDOW_H