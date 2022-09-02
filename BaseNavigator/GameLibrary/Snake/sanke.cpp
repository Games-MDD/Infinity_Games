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
#include <QDir>
Snake::Snake(QWidget *parent) : QWidget(parent)
{
    leftDir = false;
    rightDir = true;
    upDir = false;
    downDir = false;
    inGame = true;
    paused = false;
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
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
    score = 0;
    for (int i = 0; i < dots; i++) {
        x[i] = 50 - i * 10;
        y[i] = 50;
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
        qp.drawImage(appleX, appleY, apple);
        for (int i = 0; i < dots; i++) {
            if (i == 0) {
                qp.drawImage(x[i], y[i], head);
            } else {
                qp.drawImage(x[i], y[i], dot);
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
    QString message = "Game over";
    QFont font("Courier", 53, QFont::DemiBold);
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
        QString name = QInputDialog::getText(this, "Save the record", "Name: ", QLineEdit::Normal, "", &ok);
        if(ok){
            saveRecord(name);
        }
        if (QMessageBox::question(this, "Game Over!", "Would you like to play again?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
            stopGame();
        } else {
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
    QLabel *resLbl = new QLabel("");
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
    QString path = QDir::currentPath() + "/data.txt";
    QFile mFile(path);
    mFile.open(QIODevice::ReadOnly | QIODevice::Text);
    std::vector<std::pair<std::string, std::string > > vec;
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
    QString path = QDir::currentPath() + "/data.txt";
    QFile mFile(path);
    mFile.open(QIODevice::WriteOnly);
    QTextStream writeStream(&mFile);
    for(auto to: results){
        writeStream << to.second << ':' << QString::number(-to.first) << '\n';
    }
    mFile.close();
}

void Snake::HelpMessage()
{
    QMessageBox::information(this, "Help", "Press H for Help\nPress R to see Results\nPress Space to pause\resume game");
}

void Snake::clearResults()
{
    if (QMessageBox::question(this, "Clear results", "Do you really want to clear results", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
        QString path = QDir::currentPath() + "/data.txt";
        QFile mFile(path);
        mFile.open(QIODevice::WriteOnly);
        QTextStream writeStream(&mFile);
        writeStream << "";
        mFile.close();
        results.clear();
    }
}

void Snake::checkApple() {
    if ((x[0] == appleX) && (y[0] == appleY)) {
        dots++;
        score++;
        locateApple();
    }
}

void Snake::move() {
    for (int i = dots; i > 0; i--) {
        x[i] = x[(i - 1)];
        y[i] = y[(i - 1)];
    }

    if (leftDir) {
        x[0] -= DOT_SIZE;
    }

    if (rightDir) {
        x[0] += DOT_SIZE;
    }

    if (upDir) {
        y[0] -= DOT_SIZE;
    }

    if (downDir) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {
    for (int i = dots; i > 0; i--) {
        if ((i > 4) && (x[0] == x[i]) && (y[0] == y[i])) {
            inGame = false;
        }
    }

    if (y[0] >= WINDOW_HEIGHT-10) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= WINDOW_WIDTH-10) {
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

    int r = qrand() % RAND_POS_CONST;
    appleX = (r * DOT_SIZE);
    r = qrand() % RAND_POS_CONST;
    appleY = (r * DOT_SIZE);
    if (appleY >= WINDOW_HEIGHT-10) {
        locateApple();
    }
    if(appleX >= WINDOW_WIDTH - 10){
        locateApple();
    }
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

    if ((key == Qt::Key_Left) && (!rightDir)) {
        leftDir = true;
        upDir = false;
        downDir = false;
    }

    if ((key == Qt::Key_Right) && (!leftDir)) {
        rightDir = true;
        upDir = false;
        downDir = false;
    }

    if ((key == Qt::Key_Up) && (!downDir)) {
        upDir = true;
        rightDir = false;
        leftDir = false;
    }

    if ((key == Qt::Key_Down) && (!upDir)) {
        downDir = true;
        rightDir = false;
        leftDir = false;
    }

    if (key == Qt::Key_R){
        if(!paused){
            onPause();
            showResults();
            if(!resWindow->isVisible()){
                onResume();
            }
        } else {
            showResults();
        }
    }

    if(key == Qt::Key_Space){
        paused = !paused;
    }

    if(key == Qt::Key_H){
        if(!paused){
            onPause();
            HelpMessage();
            onResume();
        } else {
            HelpMessage();
        }
    }

    if(key == Qt::Key_C){
        if(!paused){
            onPause();
            clearResults();
            onResume();
        } else {
            clearResults();
        }
    }
    QWidget::keyPressEvent(e);
}
