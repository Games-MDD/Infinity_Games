#include <QCloseEvent>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QVector>

#include "results.h"

Results::Results(QVector<Result> results) {
  QVBoxLayout *dlgLayout = new QVBoxLayout();

  // Заголовок
  QLabel *textField = new QLabel(this);

  textField->setText("Date    Total time");
  textField->setAlignment(Qt::AlignCenter);
  textField->setStyleSheet("color: #0b1a2e");

  QFont fnt = textField->font();
  fnt.setPointSize(fnt.pointSize() + 1);
  textField->setFont(fnt);

  dlgLayout->addWidget(textField);

  for (int i = 0; i < results.size(); ++i) {
    QLabel *textField = new QLabel(this);

    textField->setText(results[i].date + "    " + results[i].totalTime);
    textField->setAlignment(Qt::AlignCenter);

    QFont fnt = textField->font();
    fnt.setPointSize(fnt.pointSize() + 1);
    textField->setFont(fnt);

    dlgLayout->addWidget(textField);
  }

  setLayout(dlgLayout);
}

void Results::closeEvent(QCloseEvent *event) {
  emit finished();
  event->accept();
}
