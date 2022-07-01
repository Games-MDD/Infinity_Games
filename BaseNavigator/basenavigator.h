#ifndef BASENAVIGATOR_H
#define BASENAVIGATOR_H

#include <QtWidgets>
#include "basescreensfactory.h"
class BaseNavigator : public QObject
{
    Q_OBJECT
private:
    QStackedWidget *currentContainer;
    BaseScreensFactory *screensFactory;
    QLinkedList<BaseFragment*> fragmentStack;

public:
    BaseNavigator(QStackedWidget *container, BaseScreensFactory *screenFactory);
    ~BaseNavigator();
    BaseFragment* getStartScreen();

private:
    BaseFragment* createAndConnect(QString tag);
    void connectFragment(BaseFragment* fragment);
    void disconnectFragment(BaseFragment* fragment);
public slots:
    //переход к следующему экрану по тегу
    void navigateTo(QString tag);
    //переход к предыдущему экрану
    void back();
    //заменя текущего экрана
    //TODO
    //void replace(QString tag);
    //сброси цепочки и создание нового начального экрана
    //TODO
    //void newRootScreen(QString tag);
    //переход у новому, но с данными
    //TODO
    //void navigateWhithData(QString tag,BaseModel* model);
};

#endif // BASENAVIGATOR_H
