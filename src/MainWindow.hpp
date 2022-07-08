#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QVector>

#include "Minefield/Button.hpp"
#include "Results/Results.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow() {}
  MainWindow(int, int, int);
  virtual ~MainWindow() {
    if (timer->isActive() == true)
      timer->stop();
    delete timer;
    delete timeCounter;
  }

private:
  // Размеры поля, количество мин, количество свободных клеток (не мин), количество оставшихся флагов
  int sizeX = 0, sizeY = 0, mines = 0, fieldsLeft = 0, flags = 0;

  // Состояния игры
  bool isGenerate = false, win = false, onPause = false;

  // Промежуточное время и общее время игры
  QTime *timeCounter, totalTime;
  QTimer *timer;

  // Текстовые поля
  QLabel *textField, *timeField, *pauseText;

  // Кнопки
  QPushButton *pauseButton, *resButton;
  QVector<QVector<Button *>> buttons;

  void generate(int, int);   // генерация
  void openEmpty(int, int);  // открыть пустую область
  void printVal(int, int);   // открыть одну клетку
  void minusOneFreeButton(); // расчитать оставшиеся свободные клетки

private slots:
  void clicked();                        // нажатие левой кнопки
  void newGame();                        // создание новой игры
  void pause();                          // состояние паузы
  void createWindow();                   // вызов окна с настройками
  void showResults();                    // показать окно с результатами игр
  void undisResButton();                 // разблокировать кнопку показа окна результатов
  void updateTime();                     // новая итерация таймера
  void flag();                           // поставить / убрать флаг с клетки
  void resizeEvent(QResizeEvent *event); // изменить характеристики поля под новые размеры окна
};

#endif // MAINWINDOW_H
