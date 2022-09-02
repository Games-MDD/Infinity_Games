#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hangman.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Hangman *gm = new Hangman(this);
    setCentralWidget(gm);
    gm->show();
    setFixedSize(gm->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

