#ifndef HANGMAN_H
#define HANGMAN_H

#include <QWidget>
#include <QtWidgets>
#include <QDebug>
class Hangman : public QWidget
{
   Q_OBJECT
public:
    explicit Hangman(QWidget *parent = nullptr);
    virtual void onPause();
    virtual void onResume();
public slots:
    void letterEntered();
protected:
      void paintEvent(QPaintEvent *);
      void keyPressEvent(QKeyEvent *);
private:
    QString guessedWord = "------";
    QString hiddenWord = "qwerty";
    int length = 6;
    QVector < QLabel* > letters;
    QVBoxLayout mainLayout;
    QHBoxLayout wordLayout;
    QHBoxLayout downField;
    QLineEdit entryField;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 500;
    int leftToDie = 10;
    int maxHave = 10;
    bool inGame = true;
    bool winner = true;
    QVector < QImage > images;
    QVector < QString > words;
    void initGame();
    void makeField();
    void playGame();
    void addPart();
    void checkWin();
    void gameOver();
    void drawLoose(QPainter&);
    void drawWin(QPainter&);
    void doDrawing(QPainter&);
    void makeWords();
    void chooseWord();

signals:

};

#endif // HANGMAN_H
