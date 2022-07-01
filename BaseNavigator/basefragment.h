#ifndef BASEFRAGMENT_H
#define BASEFRAGMENT_H

#include <QFrame>
class BaseFragment : public QFrame
{
    Q_OBJECT
signals:
    //сигналы посылаемые фрагментами навигатору
    void back();
    void navigateTo(QString tag);
    void newRootScreen(QString tag);
    void replace(QString tag);

    //void navigateWhithData(QString tag, BaseModel* model);
    // TODO

public:
    virtual ~BaseFragment();

    //методы для цикла жизни
    virtual void onPause();
    virtual void onResume();
    //virtual void setData(BaseModel* model);
    //TODO

};

#endif // BASEFRAGMENT_H
