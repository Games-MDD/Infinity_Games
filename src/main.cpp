#include <QApplication>
#include <QIcon>
#include <QString>

#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon("data/images/icon.png"));

  MainWindow *w = new MainWindow(9, 9, 10);
  w->setAttribute(Qt::WA_DeleteOnClose);
  w->show();

  return app.exec();
}
