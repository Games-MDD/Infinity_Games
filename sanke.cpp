#include "sanke.h"
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QInputDialog>
#include <QWidget>
#include <QLabel>
#include <QTimeEdit>
#include <QVBoxLayout>
#include <QMessageBox>
Snake::Snake(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color:yellow;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;
    paused = false;
    setFixedSize(B_WIDTH, B_HEIGHT);
    loadImages();
    loadData();
    initGame();
}

void Snake::onPause()
{
    paused = true;
}

void Snake::onResume()
{
    paused = false;
}

void Snake::loadImages() {
    dot.load(":/images/save/dot.png");
    head.load(":/images/save/head.png");
    apple.load(":/images/save/apple.png");
}

void Snake::initGame() {
    dots = 3;
    inGame = true;
    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }
    locateApple();
    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    doDrawing();
}

void Snake::doDrawing() {
    QPainter qp(this);
    if (inGame) {
        qp.drawImage(apple_x, apple_y, apple);
        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }
        QString message = QString::number(score);
        QFont font("Courier", 20, QFont::Bold);
        qp.setPen(Qt::green);
        qp.setFont(font);
        int h = height();
        int w = width();
        qp.drawText(h/2, w, message);
    } else {
        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {
    //showResults();
    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    qp.setPen(Qt::red);
    int textWidth = fm.horizontalAdvance(message);
    qp.setFont(font);
    int h = height();
    int w = width();
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
    if(!paused){
        bool ok;
        QString name = QInputDialog::getText(this, "Сохранить рекорд", "Имя: ", QLineEdit::Normal, "", &ok);
        if(ok){
            saveRecord(name);
        }
        if (QMessageBox::question(this, "Игра закончена!", "Желаете сыграть снова?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
            stopGame();
        } else {
            score = 0;
            initGame();
        }
    }
}

void Snake::saveRecord(QString aName)
{
    results.insert({-score, aName});
    saveData();
}

void Snake::showResults()
{
    resWindow = new QWidget();
    resWindow->resize(400,200);
    resWindow->setWindowTitle("Score");
    QLabel *resLbl = new QLabel("1111");
    resLbl->setGeometry(20,60,50,20);
    QString res = "";
    for(std::pair<int, QString> i: results){
        res += i.second + " : " + QString::number(-i.first)+ '\n';
    }
    resLbl->setText(res);
        resWindow->setLayout(new QVBoxLayout());
        resWindow->layout()->addWidget(resLbl);
        resWindow->show();
}

void Snake::stopGame()
{
    onPause();
}

void Snake::loadData()
{
    QFile mFile(":/data/save/data.txt");
    mFile.open(QIODevice::ReadOnly | QIODevice::Text);
    std::vector<std::pair<std::string, std::string > > vec;
    qDebug() << "23e2";
    while(!mFile.atEnd()){
        QString line = mFile.readLine();
        QString name = "";
        QString curScore = "";
        bool f = false;
        for(int i = 0; i < line.size(); i++){
            if(line[i] == ':'){
                f = true;
                continue;
            }
            if(!f){
                name += line[i];
            } else {
                curScore += line[i];
            }
        }
        results.insert({-curScore.toInt(), name});
    }
    mFile.close();
}

void Snake::saveData()
{
    QFile mFile(":/data/save/data.txt");
    mFile.open(QIODevice::WriteOnly);
    QTextStream writeStream(&mFile);
    for(auto to: results){
        writeStream << to.second << ' ' << QString::number(to.first) << '\n';
    }
    mFile.close();
}

void Snake::checkApple() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        dots++;
        score++;
        locateApple();
    }
}

void Snake::move() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {

    for (int z = dots; z > 0; z--) {
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void Snake::locateApple() {
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);
    if (inGame && !paused) {
        checkApple();
        checkCollision();
        move();
    }
    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if (key == Qt::Key_R){
        showResults();
    }

    if(key == Qt::Key_Space){
        paused = !paused;
    }

    if(key == Qt::Key_H){

    }
    QWidget::keyPressEvent(e);
}
