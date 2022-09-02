#ifndef RESULTS_H
#define RESULTS_H

#include <QDate>
#include <QDialog>
#include <QLabel>
#include <QString>
#include <QTime>
#include <QVector>

struct Result {
  QString date;
  QString totalTime;
};

class Results : public QDialog {
  Q_OBJECT

public:
  Results(QVector<Result>);
  virtual ~Results() {}

private slots:
  void closeEvent(QCloseEvent *event);

signals:
  void finished();
};

#endif // RESULTS_H
