#include "testwindow.h"
#include "ui_testwindow.h"

testWindow::testWindow(QMainWindow *parent)
    : QMainWindow(parent), ui(new Ui::testWindow) {
  ui->setupUi(this);
  setGeometry(0, 0, 1000, 1000);
  Breakout *breakout = new Breakout(this);
  setCentralWidget(breakout);
}

testWindow::~testWindow() { delete ui; }
