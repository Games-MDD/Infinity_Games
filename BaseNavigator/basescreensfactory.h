#ifndef BASESCREENSFACTORY_H
#define BASESCREENSFACTORY_H

#include "basefragment.h"
class BaseScreensFactory
{
public:
    virtual ~BaseScreensFactory();

    virtual BaseFragment* create(QString tag);
    // создание экрана по тегу
    virtual QString createStart();
    // возврат тега стартового экрана
};

#endif // BASESCREENSFACTORY_H
