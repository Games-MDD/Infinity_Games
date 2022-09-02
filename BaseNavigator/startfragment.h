#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include "basefragment.h"
#include <QDebug>
#include <QtWidgets>
class StartFragment : public BaseFragment {
  Q_OBJECT
//signals:
//  //сигналы посылаемые фрагментами навигатору
//  void back();
//  void navigateTo(QString tag);
//  void newRootScreen(QString tag);
//  void replace(QString tag);

public:
  StartFragment();
  ~StartFragment();
public slots:
  void StartNewGame();

private:
  QStandardItemModel *GameTagsModel;
  QListView *GameTagsListView;
};

#endif // STARTFRAGMENT_H
