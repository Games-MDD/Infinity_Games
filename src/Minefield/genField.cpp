#include <QDebug>
#include <ctime>
#include <iostream>
#include <vector>

#include "genField.hpp"

void init(QVector<QVector<int>> &src, int SIZE_X, int SIZE_Y, int firstStepX, int firstStepY, int NUM_MINES) {

  // Начальное заполнение
  for (int i = 0; i < SIZE_X; i++) {
    for (int j = 0; j < SIZE_Y; j++)
      src[i][j] = 0;
  }
  // Расстановка мин
  for (int i = 0; i < NUM_MINES; i++) {
    int x, y;
    while (true) {
      x = rand() % SIZE_X;
      y = rand() % SIZE_Y;
      if (src[x][y] != -1 && x != firstStepX && y != firstStepY) {
        src[x][y] = -1;
        break;
      }
    }
  }
  // Расстановка цифр
  for (int i = 0; i < SIZE_X; i++)
    for (int j = 0; j < SIZE_Y; j++) {
      int count = 0;
      if (src[i][j] != -1) { // если это не мина
        if (j > 0) {         // три клетки выше текущей
          if (i > 0 && src[i - 1][j - 1] == -1)
            count++;
          if (src[i][j - 1] == -1)
            count++;
          if (i < SIZE_X - 1 && src[i + 1][j - 1] == -1)
            count++;
        }

        if (i > 0 && src[i - 1][j] == -1) // клетка слева
          count++;
        if (i < SIZE_X - 1 && src[i + 1][j] == -1) // клетка справа
          count++;

        if (j < SIZE_Y) { // три клетки ниже текущей
          if (i > 0 && src[i - 1][j + 1] == -1)
            count++;
          if (src[i][j + 1] == -1)
            count++;
          if (i < SIZE_X - 1 && src[i + 1][j + 1] == -1)
            count++;
        }

        src[i][j] = count;
      }
    }
}

QVector<QVector<int>> getNewField(int stepX, int stepY, int sizeX, int sizeY, int mines) {
  srand(time(nullptr));

  QVector<QVector<int>> field = QVector<QVector<int>>(sizeX, QVector<int>(sizeY));
  init(field, sizeX, sizeY, stepX, stepY, mines);

  return field;
}
