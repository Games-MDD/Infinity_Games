#include "hangman.h"

Hangman::Hangman(QWidget *parent) : QWidget(parent)
{
    makeWords();
    makeField();
    initGame();
    connect(&entryField, SIGNAL(editingFinished()), this, SLOT(letterEntered()));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Hangman::onPause()
{
    inGame = false;
}

void Hangman::onResume()
{
    inGame = true;
}

void Hangman::initGame()
{
    inGame = true;
    leftToDie = 10;
    winner = true;
    entryField.setReadOnly(false);
    for(int i = 0; i < letters.size(); i++){
        letters[i]->clear();
        letters[i]->deleteLater();
        wordLayout.removeWidget(letters[i]);
    }
    //дописать выбор случайного слова
    chooseWord();
    letters.resize(hiddenWord.size());
    for(int i = 0; i < letters.size(); i++){
        letters[i] = new QLabel();
        letters[i]->setText("");
        letters[i]->setFixedSize(50, 50);
        letters[i]->setAlignment(Qt::AlignCenter);
        letters[i]->setStyleSheet("border:1px solid;");
        wordLayout.addWidget(letters[i]);
    }

}

void Hangman::makeField()
{
//    letters.resize(hiddenWord.size());
//    for(int i = 0; i < letters.size(); i++){
//        letters[i] = new QLabel();
//        letters[i]->setText("");
//        letters[i]->setFixedSize(50, 50);
//        letters[i]->setAlignment(Qt::AlignCenter);
//        letters[i]->setStyleSheet("border:1px solid;");
//        wordLayout.addWidget(letters[i]);
//    }
    wordLayout.setAlignment(Qt::AlignCenter);
    mainLayout.addLayout(&wordLayout);

    mainLayout.setAlignment(Qt::AlignTop);
    mainLayout.setAlignment(Qt::AlignHCenter);

    mainLayout.addSpacing(300);

    entryField.setFixedSize(50, 50);
    downField.addWidget(&entryField);
    mainLayout.addLayout(&downField);

    setLayout(&mainLayout);
    QRegExp rx("[a-z]");
    QValidator *validator = new QRegExpValidator(rx, this);
    entryField.setValidator(validator);
    entryField.setAlignment(Qt::AlignCenter);
    entryField.setStyleSheet("font: bold 50px");
    QString path = ":/images/save/";
    QImage cur = QImage(path + "/0.png");
    images.push_back(cur);
    cur = QImage(path + "/1.png");
    images.push_back(cur);
    cur = QImage(path + "/2.png");
    images.push_back(cur);
    cur = QImage(path + "/3.png");
    images.push_back(cur);
    cur = QImage(path + "/4.png");
    images.push_back(cur);
    cur = QImage(path + "/5.png");
    images.push_back(cur);
    cur = QImage(path + "/6.png");
    images.push_back(cur);
    cur = QImage(path + "/7.png");
    images.push_back(cur);
    cur = QImage(path + "/8.png");
    images.push_back(cur);
    cur = QImage(path + "/9.png");
    images.push_back(cur);
    cur = QImage(path + "/10.png");
    images.push_back(cur);
}

void Hangman::playGame()
{

}

void Hangman::addPart()
{
    if(leftToDie){
        leftToDie--;
        update();
    }
    if(!leftToDie){
        winner = false;
        inGame = false;
    }
}

void Hangman::checkWin()
{
    qDebug() << hiddenWord << ' ' << guessedWord;
    if(hiddenWord == guessedWord){
        winner = true;
        inGame = false;
    }
}

void Hangman::gameOver()
{
    entryField.setReadOnly(true);
    if(winner){
        qDebug() << "win";
    } else {
        qDebug() << "Loose";
    }
    update();
}

void Hangman::drawLoose(QPainter &qp)
{
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
    if (QMessageBox::question(this, "Игра закончена!", "Желаете сыграть снова?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
        //????????
    } else {
        initGame();
    }
}

void Hangman::drawWin(QPainter &qp)
{
    QString message = "YOU WIN";
    QFont font("Courier", 70, QFont::DemiBold);
    QFontMetrics fm(font);
    qp.setPen(Qt::yellow);
    int textWidth = fm.horizontalAdvance(message);
    qp.setFont(font);
    int h = height();
    int w = width();
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
    if (QMessageBox::question(this, "Game Over!", "Would you like to play again?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
        //????????
    } else {
        initGame();
    }
}

void Hangman::doDrawing(QPainter &qp)
{
    int n = maxHave - leftToDie;
    for(int i = 0; i <= n; i++){
        int h = height();
        int w = width();
        qp.drawImage(w/2 - 150, h/2 - 150, images[i]);
    }
}

void Hangman::makeWords()
{
    words.push_back("remuneration");
    words.push_back("aluminium");
    words.push_back("anaesthetist");
    words.push_back("anonymous");
    words.push_back("ethnicity");
    words.push_back("facilitate");
    words.push_back("february");
    words.push_back("statistics");
    words.push_back("pronunciation");
    words.push_back("prejudice");
    words.push_back("education");
    words.push_back("government");
    words.push_back("affection");
    words.push_back("amazement");
    words.push_back("breakthrough");
    words.push_back("incomprehensibilities");
    words.push_back("sesquipedalianism");
    words.push_back("incomprehensibility");
    words.push_back("strengths");
    words.push_back("spreadsheet");
    words.push_back("shortcoming");
    words.push_back("frequency");
    words.push_back("bottleneck");
    words.push_back("capacity");
    words.push_back("coherency");
}

void Hangman::chooseWord()
{
    qsrand(time(0));
    int pos = rand() % words.size();
    qDebug() << pos;
    hiddenWord = words[pos];
    length = hiddenWord.size();
    guessedWord = hiddenWord;
    for(int i = 0; i < length; i++){
        guessedWord[i] = '-';
    }
}

void Hangman::letterEntered()
{
    if(inGame){
        emit entryField.returnPressed();
        QString letter = entryField.text();
        bool ok = false;
        for(int i = 0; i < length; i++){
            if(hiddenWord[i] == letter){
                ok = true;
                letters[i]->setText(letter);
                guessedWord[i] = letter[0];
            }
        }
        if(!ok){
            qDebug() <<"Paert";
            addPart();
        }
        entryField.clear();
        checkWin();
        if(!inGame){
            gameOver();
        }
    }
}

void Hangman::paintEvent(QPaintEvent *)
{
    QPainter qp(this);
    if(inGame){
        doDrawing(qp);
    } else {
        if(!winner){
            drawLoose(qp);
        } else {
            doDrawing(qp);
            drawWin(qp);
        }
    }

    //doDrawing();
}

void Hangman::keyPressEvent(QKeyEvent *e)
{

}

