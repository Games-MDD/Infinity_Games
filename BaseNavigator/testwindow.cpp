#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TestWindow) {
  ui->setupUi(this);
  container = new QStackedWidget;
  factory = new ScreensFactory;
  navigator = new BaseNavigator(container, factory);
  setCentralWidget(container);
}

TestWindow::~TestWindow() { delete ui; }
