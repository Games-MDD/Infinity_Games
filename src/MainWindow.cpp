#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QResizeEvent>
#include <QSpacerItem>
#include <QStatusBar>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "MainWindow.hpp"
#include "Minefield/Change.hpp"
#include "Minefield/genField.hpp"
#include "Results/Results.hpp"
#include "Results/insert/insertIntoDB.hpp"
#include "Results/select/selectFromDB.hpp"

#define sendButton qobject_cast<Button *>

MainWindow::MainWindow(int x, int y, int m) : sizeX(x), sizeY(y), mines(m) {

  // Подключение таблицы стилей
  QFile styleF;
  styleF.setFileName("data/qss/style.css");
  styleF.open(QFile::ReadOnly);
  QString qssStr = styleF.readAll();
  this->setStyleSheet(qssStr);

  // Необходимые слои
  QVBoxLayout *dlgLayout = new QVBoxLayout();
  QHBoxLayout *header = new QHBoxLayout();

  // Кнопка Again
  QPushButton *startNewGame = new QPushButton(this);

  startNewGame->setText("Again");
  startNewGame->setFocusPolicy(Qt::NoFocus);
  startNewGame->setStyleSheet("background: #f1f5ce;");
  connect(startNewGame, SIGNAL(clicked()), this, SLOT(newGame()));

  header->addWidget(startNewGame);

  // Кнопка Pause
  pauseButton = new QPushButton(this);

  pauseButton->setText("Pause");
  pauseButton->setFocusPolicy(Qt::NoFocus);
  pauseButton->setStyleSheet("background: #e8f4ff");
  connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));

  header->addWidget(pauseButton);

  // Кнопка ChangeWindow
  QPushButton *changeWindow = new QPushButton(this);

  changeWindow->setText("Change");
  changeWindow->setFocusPolicy(Qt::NoFocus);
  changeWindow->setStyleSheet("background: #e6f5df;");
  connect(changeWindow, SIGNAL(clicked()), this, SLOT(createWindow()));

  header->addWidget(changeWindow);
  dlgLayout->addLayout(header);

  // Сообщение при паузе
  pauseText = new QLabel(this);
  pauseText->setText("Pause");
  pauseText->setStyleSheet("padding-top: 50px");

  QFont fntP = pauseText->font();
  fntP.setPointSize(fntP.pointSize() + 5);
  pauseText->setFont(fntP);
  pauseText->setVisible(false);

  dlgLayout->addWidget(pauseText);

  // Небольшой отступ
  dlgLayout->addItem(new QSpacerItem(0, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

  // Кнопки поля
  buttons = QVector<QVector<Button *>>(sizeX, QVector<Button *>(sizeY));

  QGridLayout *buttonField = new QGridLayout();

  for (int i = 0; i < sizeX; i++) {
    for (int j = 0; j < sizeY; j++) {
      Button *button = new Button(0, i, j, this);

      button->setStyleSheet("background: white");
      button->setFixedSize(QSize(42, 42));
      button->setFocusPolicy(Qt::NoFocus);

      QFont fnt;
      fnt.setPointSize(15);
      button->setFont(fnt);

      buttonField->addWidget(button, j, i);

      // Нажатие кнопки вызывает событие в классе Field
      connect(button, SIGNAL(clicked()), this, SLOT(clicked()));
      connect(button, SIGNAL(flag()), this, SLOT(flag()));

      buttons[i][j] = button;
    }
  }

  buttonField->setSpacing(0);

  dlgLayout->addLayout(buttonField);
  dlgLayout->setAlignment(buttonField, Qt::AlignCenter);

  // Небольшой отступ
  dlgLayout->addItem(new QSpacerItem(0, 7, QSizePolicy::Expanding, QSizePolicy::Expanding));

  // Центральный виджет
  QWidget *window = new QWidget();
  window->setLayout(dlgLayout);
  setCentralWidget(window);

  // Статус бар
  QStatusBar *statusBar = this->statusBar();

  // Текстовое поле
  textField = new QLabel(this);

  textField->setText("Are you ready?");
  textField->setObjectName("textField");
  textField->setAlignment(Qt::AlignLeft);

  QFont fnt = textField->font();
  fnt.setPointSize(fnt.pointSize() + 1);
  textField->setFont(fnt);

  statusBar->addWidget(textField);

  // Поле таймера
  timeField = new QLabel(this);

  timeField->setText("00:00:00");
  timeField->setObjectName("timeField");
  timeField->setAlignment(Qt::AlignRight);

  fnt = timeField->font();
  fnt.setPointSize(fnt.pointSize() + 1);
  timeField->setFont(fnt);

  timeCounter = new QTime(0, 0);
  totalTime = QTime(0, 0);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

  statusBar->addPermanentWidget(timeField);

  // Кнопка Results
  resButton = new QPushButton(this);

  resButton->setText("Show results");
  resButton->setObjectName("showResult");
  resButton->setFocusPolicy(Qt::NoFocus);
  resButton->setMaximumSize(80, 30);
  connect(resButton, SIGNAL(clicked()), this, SLOT(showResults()));

  statusBar->addPermanentWidget(resButton);
  statusBar->setSizeGripEnabled(false);

  // Почему-то ругается
  //results = getTable(sizeX, sizeY, mines);
}

void MainWindow::clicked() {

  // Получение информации из объекта, отправившего событие
  int x = sendButton(sender())->xCord, y = sendButton(sender())->yCord;

  if (!isGenerate) { // сгенерировать
    generate(x, y);
    isGenerate = true;

    timer->start(1000);
  }

  switch (sendButton(sender())->val) {
  case 0: { // чисто
    openEmpty(x, y);
    break;
  }
  case -1: { // бомба
    win = true;
    textField->setText("You lose");
    timer->stop();

    // Отключить кнопки и открыть все бомбы
    for (QVector<Button *> vec : buttons)
      for (auto button : vec) {
        if (button->val == -1) {
          QPixmap pixmap("data/images/bomb.png");
          QIcon ButtonIcon(pixmap);
          button->setIcon(ButtonIcon);
        }
        button->setEnabled(false);
      }
    sendButton(sender())->setStyleSheet("background: #e83a3a;");
    break;
  }
  default: {
    minusOneFreeButton();
    printVal(x, y);
    break;
  }
  }
}

void MainWindow::generate(int x, int y) { // сгенерировать новую карту
  QVector<QVector<int>> genField = getNewField(x, y, sizeX, sizeY, mines);

  for (int i = 0; i < sizeX; i++)
    for (int j = 0; j < sizeY; j++)
      buttons[i][j]->val = genField[i][j];

  fieldsLeft = sizeX * sizeY - mines;
  flags = mines;
}

void MainWindow::openEmpty(int x, int y) { // открытие пустой области
  // Открываем текущую клетку
  printVal(x, y);
  if (buttons[x][y]->isFlagged) // убрать флаг, если он на клетке
    ++flags;

  // Рекурсивный спуск
  if (y > 0) { // три клетки выше текущей

    if (x > 0 && buttons[x - 1][y - 1]->val != -1 && buttons[x - 1][y - 1]->val != 0 && !buttons[x - 1][y - 1]->isOpen) {
      printVal(x - 1, y - 1);
      if (buttons[x - 1][y - 1]->isFlagged)
        ++flags;
      --fieldsLeft;
    }

    if (buttons[x][y - 1]->val == 0) {
      if (!buttons[x][y - 1]->isOpen)
        this->openEmpty(x, y - 1);
    } else if (buttons[x][y - 1]->val != -1 && !buttons[x][y - 1]->isOpen) {
      printVal(x, y - 1);
      if (buttons[x][y - 1]->isFlagged)
        ++flags;
      --fieldsLeft;
    }

    if (x < sizeX - 1 && buttons[x + 1][y - 1]->val != -1 && buttons[x + 1][y - 1]->val != 0 && !buttons[x + 1][y - 1]->isOpen) {
      printVal(x + 1, y - 1);
      if (buttons[x + 1][y - 1]->isFlagged)
        ++flags;
      --fieldsLeft;
    }
  }

  if (x > 0) { // клетка слева
    if (buttons[x - 1][y]->val == 0) {
      if (!buttons[x - 1][y]->isOpen)
        openEmpty(x - 1, y);
    } else if (buttons[x - 1][y]->val != -1 && !buttons[x - 1][y]->isOpen) {
      printVal(x - 1, y);
      if (buttons[x - 1][y]->isFlagged)
        ++flags;
      --fieldsLeft;
    }
  }

  if (x < sizeX - 1) { // клетка справа
    if (buttons[x + 1][y]->val == 0) {
      if (!buttons[x + 1][y]->isOpen)
        openEmpty(x + 1, y);
    } else if (buttons[x + 1][y]->val != -1 && !buttons[x + 1][y]->isOpen) {
      printVal(x + 1, y);
      if (buttons[x + 1][y]->isFlagged)
        ++flags;
      --fieldsLeft;
    }
  }
  if (y < sizeY - 1) { // три клетки ниже текущей

    if (x > 0 && buttons[x - 1][y + 1]->val != -1 && buttons[x - 1][y + 1]->val != 0 && !buttons[x - 1][y + 1]->isOpen) {
      printVal(x - 1, y + 1);
      if (buttons[x - 1][y + 1]->isFlagged)
        ++flags;
      --fieldsLeft;
    }

    if (buttons[x][y + 1]->val == 0) {
      if (!buttons[x][y + 1]->isOpen)
        openEmpty(x, y + 1);
    } else if (buttons[x][y + 1]->val != -1 && !buttons[x][y + 1]->isOpen) {
      printVal(x, y + 1);
      if (buttons[x][y + 1]->isFlagged)
        ++flags;
      --fieldsLeft;
    }

    if (x < sizeX - 1 && buttons[x + 1][y + 1]->val != -1 && buttons[x + 1][y + 1]->val != 0 && !buttons[x + 1][y + 1]->isOpen) {
      printVal(x + 1, y + 1);
      if (buttons[x + 1][y + 1]->isFlagged)
        ++flags;
      --fieldsLeft;
    }
  }

  // Вывод оставшихся свободных клеток
  minusOneFreeButton();
}

void MainWindow::minusOneFreeButton() { // пересчет отставшихся пустых клеток
  if (--fieldsLeft == 0) {              // конец игры
    win = true;

    textField->setText("Win!");
    timer->stop();

    // Отключить все кнопки
    for (QVector<Button *> vec : buttons)
      for (auto button : vec)
        button->setEnabled(false);

    // Расчет времени
    updateTime();

//    addToTable(sizeX, sizeY, mines, result);
//   results = getTable(sizeX, sizeY, mines);

  } else { // иначе обновить поле в статус баре
    QString strOut, strFlags;
    strOut.setNum(fieldsLeft);
    strFlags.setNum(flags);
    textField->setText("Осталось: " + strOut + " своб.  Флагов: " + strFlags);
  }
}

void MainWindow::printVal(int x, int y) { // открыть клетку

  buttons[x][y]->setIcon(QIcon());

  QString str;
  if (buttons[x][y]->val == 0) {
    str = "";
    buttons[x][y]->setStyleSheet("background: #ebe8d8");
  } else {
    str.setNum(buttons[x][y]->val);

    // У каждой цифры свой цвет
    switch (buttons[x][y]->val) {
    case 1: { // синий
      buttons[x][y]->setStyleSheet("color: #4236eb; font-weight: 900; background: #ebe8d8");
      break;
    }
    case 2: { // зеленый
      buttons[x][y]->setStyleSheet("color: #208c27; font-weight: 900; background: #ebe8d8");
      break;
    }
    case 3: { // красный
      buttons[x][y]->setStyleSheet("color: #c75454; font-weight: 900; background: #ebe8d8");
      break;
    }
    case 4: { // тоже синий, но потемнее
      buttons[x][y]->setStyleSheet("color: #50359c; font-weight: 900; background: #ebe8d8");
      break;
    }
    case 5: { // бордовый
      buttons[x][y]->setStyleSheet("color: #872f2f; font-weight: 900; background: #ebe8d8");
      break;
    }
    case 6: { // болотный какой-то
      buttons[x][y]->setStyleSheet("color: #83a30f; font-weight: 900; background: #ebe8d8");
      break;
    }
    case 7: { // темно-синий
      buttons[x][y]->setStyleSheet("color: #302e75; font-weight: 900; background: #ebe8d8");
      break;
    }
    case 8: { // черный
      buttons[x][y]->setStyleSheet("color: black; font-weight: 900; background: #ebe8d8");
      break;
    }
    }
  }

  buttons[x][y]->setEnabled(false);
  buttons[x][y]->setText(str);
  buttons[x][y]->isOpen = true;
}

void MainWindow::flag() { // установка / снятие флага
  if (isGenerate) {

    // Получение информации из объекта, отправившего событие
    int x = sendButton(sender())->xCord, y = sendButton(sender())->yCord;

    if (!sendButton(sender())->isFlagged) { // поставить флаг
      if (flags > 0) {

        QPixmap pixmap("data/images/flag.png");
        QIcon ButtonIcon(pixmap);
        buttons[x][y]->setIcon(ButtonIcon);

        buttons[x][y]->isFlagged = true;
        QFont fnt = buttons[x][y]->font();
        fnt.setPointSize(fnt.pointSize() - 2);
        buttons[x][y]->setFont(fnt);

        --flags;
        QString strOut, strFlags;
        strOut.setNum(fieldsLeft);
        strFlags.setNum(flags);
        textField->setText("Осталось: " + strOut + " своб.  Флагов: " + strFlags);
      }
    } else { // убрать флаг
      buttons[x][y]->setIcon(QIcon());
      buttons[x][y]->isFlagged = false;
      QFont fnt = buttons[x][y]->font();
      fnt.setPointSize(15);
      buttons[x][y]->setFont(fnt);

      ++flags;
      QString strOut, strFlags;
      strOut.setNum(fieldsLeft);
      strFlags.setNum(flags);
      textField->setText("Осталось: " + strOut + " своб.  Флагов: " + strFlags);
    }
  }
}

void MainWindow::newGame() { // сброс всего к начальным

  pauseText->setVisible(false); // убрать сообщение о паузе
  pauseButton->setText("Pause");

  for (QVector<Button *> vec : buttons) // обнулить состояние поля
    for (auto button : vec) {
      button->val = 0;
      button->isFlagged = false;
      button->isOpen = false;
      button->setText("");
      button->setIcon(QIcon());
      button->setEnabled(true);
      button->setVisible(true);
      button->setStyleSheet("background: white");
      QFont fnt;
      fnt.setPointSize(15);
      button->setFont(fnt);
    }

  textField->setText("Oh, OK"); // обнулить переменные
  isGenerate = false;
  win = false;
  onPause = false;
  fieldsLeft = 0;
  flags = 0;

  if (timer->isActive() == true) // сбросить таймер
    timer->stop();
  timeCounter = new QTime(0, 0);
  totalTime = QTime(0, 0);
  timeField->setText("00:00:00");
}

void MainWindow::pause() { // состояние паузы
  if (isGenerate && !win) {
    if (!onPause) { // поставить игру на паузу
      // Скрыть поле
      for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
          buttons[i][j]->setVisible(false);

      // Остановка таймера и сохранение текущего времени
      timer->stop();
      updateTime();

      // Вывод надписи Pause и изменение названия кнопки
      pauseText->setVisible(true);
      pauseText->setAlignment(Qt::AlignCenter);
      pauseButton->setText("Resume");

      onPause = true;
    } else {
      // Скрыть надпись
      pauseText->setVisible(false);
      pauseButton->setText("Pause");

      // Показать поле
      for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
          buttons[i][j]->setVisible(true);

      // Возобновить таймер
      //timeCounter->restart();
      timer->start();

      onPause = false;
    }
  }
}

void MainWindow::updateTime() { // обновление поля таймера каждую секунду
  //totalTime = totalTime.addMSecs(timeCounter->elapsed());
  timeField->setText(totalTime.toString("hh:mm:ss"));
  //timeCounter->restart(); // перезапуск счетчика
}

void MainWindow::createWindow() { // открыть диалоговое окно с настройками поля
  if (timer->isActive() == true)
    timer->stop();

  Change *answ = new Change(sizeX, sizeY, mines);
  answ->setAttribute(Qt::WA_DeleteOnClose, true); // для того, чтобы объект самоуничтожился после выполнения
  answ->show();

  deleteLater();
  this->close(); // закрыть текущее окно
}

void MainWindow::undisResButton() { // вернуть кнопку в активное состояние
  resButton->setEnabled(true);
  resButton->setObjectName("showResult");
}

void MainWindow::resizeEvent(QResizeEvent *event) { // пропорциональное изменение размера кнопок поля
  QMainWindow::resizeEvent(event);

  // Новая ширина кнопок         для корректного отображения на горизонтальных окнах
  int wButton = this->width() / 10, maxHeight = this->height() - 100;

  if (sizeY * wButton >= maxHeight) // если поле выходит за границы окна
    wButton = maxHeight / sizeY;

  for (int i = 0; i < sizeX; i++) {
    for (int j = 0; j < sizeY; j++) {
      buttons[i][j]->setFixedSize(QSize(wButton, wButton));            // размер кнопки
      buttons[i][j]->setIconSize(QSize(wButton * 0.8, wButton * 0.8)); // размер иконки
    }
  }
}
