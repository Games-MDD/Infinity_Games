#include "infinityengine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InfinityEngine w;
    w.show();

    return a.exec();
}
