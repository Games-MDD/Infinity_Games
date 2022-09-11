#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TestWindow) {
  ui->setupUi(this);
  container = new QStackedWidget;
  factory = new ScreensFactory;
  navigator = new BaseNavigator(container, factory);
  setCentralWidget(container);
  //set GUI

  //set title
  setWindowTitle("Infinity Games");
  setWindowIcon(QIcon(":/icon/Resource/WindowIcon.png"));
    setPalette(QPalette(Qt::GlobalColor::gray));

}

TestWindow::~TestWindow() { delete ui; }
