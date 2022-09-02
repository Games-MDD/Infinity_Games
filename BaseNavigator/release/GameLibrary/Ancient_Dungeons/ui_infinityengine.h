/********************************************************************************
** Form generated from reading UI file 'infinityengine.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFINITYENGINE_H
#define UI_INFINITYENGINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfinityEngine
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *InfinityEngine)
    {
        if (InfinityEngine->objectName().isEmpty())
            InfinityEngine->setObjectName(QString::fromUtf8("InfinityEngine"));
        InfinityEngine->resize(800, 600);
        centralwidget = new QWidget(InfinityEngine);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        InfinityEngine->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InfinityEngine);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        InfinityEngine->setMenuBar(menubar);

        retranslateUi(InfinityEngine);

        QMetaObject::connectSlotsByName(InfinityEngine);
    } // setupUi

    void retranslateUi(QMainWindow *InfinityEngine)
    {
        InfinityEngine->setWindowTitle(QCoreApplication::translate("InfinityEngine", "InfinityEngine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfinityEngine: public Ui_InfinityEngine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFINITYENGINE_H
