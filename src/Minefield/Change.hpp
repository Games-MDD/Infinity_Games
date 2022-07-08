#ifndef CHANGE_H
#define CHANGE_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

class Change: public QDialog
{
    Q_OBJECT

    public:
         Change(int, int, int);
         virtual ~Change() {
             delete textField;
             delete width;
             delete height;
             delete mines;
             delete save;
         }

    private:
         QLabel *textField;
         QSpinBox *width;
         QSpinBox *height;
         QSpinBox *mines;
         QPushButton *save;
    private slots:
         void createNew();
         void redButton();
};

#endif // CHANGE_H
