#include "testwindow.h"

#include <QApplication>
#include "breakout.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testWindow w;
    w.show();

    return a.exec();
}
