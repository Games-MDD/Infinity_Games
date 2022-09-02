/********************************************************************************
** Form generated from reading UI file 'testwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWINDOW_H
#define UI_TESTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testWindow
{
public:

    void setupUi(QWidget *testWindow)
    {
        if (testWindow->objectName().isEmpty())
            testWindow->setObjectName(QString::fromUtf8("testWindow"));
        testWindow->resize(800, 600);

        retranslateUi(testWindow);

        QMetaObject::connectSlotsByName(testWindow);
    } // setupUi

    void retranslateUi(QWidget *testWindow)
    {
        testWindow->setWindowTitle(QCoreApplication::translate("testWindow", "testWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testWindow: public Ui_testWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
