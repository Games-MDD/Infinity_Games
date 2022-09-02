#include <QApplication>
#include <QIcon>
#include <QString>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/images/Resources/Images/icon.png"));

  MainWindow *w = new MainWindow(9, 9, 10);
  w->setAttribute(Qt::WA_DeleteOnClose);
  w->show();

  return app.exec();
}
