#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../MainWindow.hpp"
#include "Change.hpp"

Change::Change(int w, int h, int m) {
  QVBoxLayout *dlgLayout = new QVBoxLayout();

  // Текстовое поле
  textField = new QLabel(this);

  textField->setText("Введите характеристики нового окна");
  textField->setAlignment(Qt::AlignCenter);

  QFont fnt = textField->font();
  fnt.setPointSize(fnt.pointSize() + 1);
  textField->setFont(fnt);

  dlgLayout->addWidget(textField);

  dlgLayout->addItem(new QSpacerItem(0, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

  QGridLayout *spinboxes = new QGridLayout();

  QLabel *label1 = new QLabel(tr("Ширина:"));
  width = new QSpinBox(this);
  width->setSingleStep(1);
  width->setMinimum(1);
  width->setValue(w);

  QLabel *label2 = new QLabel(tr("Высота:"));
  height = new QSpinBox(this);
  height->setSingleStep(1);
  height->setMinimum(1);
  height->setValue(h);

  QLabel *label3 = new QLabel(tr("Мины:"));
  mines = new QSpinBox(this);
  mines->setSingleStep(1);
  mines->setValue(m);

  spinboxes->addWidget(label1, 0 / 3, 0 % 3);
  spinboxes->addWidget(label2, 1 / 3, 1 % 3);
  spinboxes->addWidget(label3, 2 / 3, 2 % 3);

  spinboxes->addWidget(width, 3 / 3, 3 % 3);
  spinboxes->addWidget(height, 4 / 3, 4 % 3);
  spinboxes->addWidget(mines, 5 / 3, 5 % 3);

  dlgLayout->addLayout(spinboxes);

  dlgLayout->addItem(new QSpacerItem(0, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

  save = new QPushButton(this);

  save->setText("Save");
  save->setFocusPolicy(Qt::NoFocus);

  connect(save, SIGNAL(clicked()), this, SLOT(createNew()));

  dlgLayout->addWidget(save);

  setLayout(dlgLayout);
}

void Change::createNew() {
  if (mines->value() >= width->value() * height->value()) {
    save->setStyleSheet("background: #f2b6b6;");
    textField->setText("Слишком много мин!");
    // Кнопка краснеет на 2 секунды
    QTimer::singleShot(2000, this, SLOT(redButton()));
  } else {
    MainWindow *newField = new MainWindow(width->value(), height->value(), mines->value());
    newField->setAttribute(Qt::WA_DeleteOnClose, true);
    newField->show();

    deleteLater();
    this->close(); // закрыть текущее окно
  }
}

void Change::redButton() { // покраснение спало, фух
  save->setStyleSheet("background: white");
  textField->setText("Введите характеристики нового окна");
}
