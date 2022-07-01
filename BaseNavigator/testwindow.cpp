#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    container= new QStackedWidget;
    factory= new ScreensFactory;
    navigator= new BaseNavigator(container,factory);
    navigator->navigateTo("GAME");
    navigator->back();
    navigator->navigateTo("GAME");
    QHBoxLayout* mainLayout=new QHBoxLayout;
    mainLayout->addWidget(container);
    this->setLayout(mainLayout);
}

TestWindow::~TestWindow()
{
    delete ui;
}

