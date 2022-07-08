#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "../connection/connectDB.hpp"

int main() {

  QSqlDatabase db = connectDB("../connection/config");
  if (db.open()) {

    QSqlQuery query;
    if (query.exec(
            "CREATE TABLE public.results(id SERIAL, date DATE NOT NULL, width INTEGER NOT NULL, height INTEGER NOT NULL, mines INTEGER NOT NULL, "
            "totalTime TIME NOT NULL);"
            "ALTER TABLE ONLY public.results "
            "ADD CONSTRAINT mines_val CHECK (mines < width*height);")) {
      qDebug() << "Ok";
      db.close();
      return 0;
    }

    qDebug() << "Произошла ошибка при создании таблицы";
    db.close();
  }

  qDebug() << "Ошибка соединения с бд";
  return 1;
}