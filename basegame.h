#ifndef BASEGAME_H
#define BASEGAME_H
#include <QString>
#include <QDialog>
#include <QShowEvent>

class BaseGame:public QDialog
{
public:
    BaseGame();
    void showEvent(QShowEvent* event);
    virtual QString getName() = 0;
    virtual int numMuves() = 0;
signals:
    void showedUp();
protected:
    QString name;
    int moves;
};
#endif // BASEGAME_H
