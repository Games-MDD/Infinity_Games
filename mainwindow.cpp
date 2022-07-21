#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sanke.h"
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Snake *gm = new Snake(this);
    //setCentralWidget(gm);
    gm->show();
    //gm->initGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

