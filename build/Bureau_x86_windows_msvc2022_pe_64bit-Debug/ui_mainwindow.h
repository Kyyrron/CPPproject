/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridWidget;
    QGridLayout *grid;
    QLineEdit *xSpeedLine;
    QLineEdit *massLine;
    GLWidget *myGLWidget;
    QLineEdit *ySpeedLine;
    QPushButton *clearButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 700);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(29, 0, 193);\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(29, 0, 193);\n"
"\n"
""));
        gridWidget = new QWidget(centralwidget);
        gridWidget->setObjectName("gridWidget");
        gridWidget->setGeometry(QRect(0, 0, 700, 700));
        gridWidget->setAutoFillBackground(false);
        grid = new QGridLayout(gridWidget);
        grid->setSpacing(0);
        grid->setObjectName("grid");
        grid->setContentsMargins(0, 0, 0, 0);
        xSpeedLine = new QLineEdit(gridWidget);
        xSpeedLine->setObjectName("xSpeedLine");

        grid->addWidget(xSpeedLine, 0, 0, 1, 1);

        massLine = new QLineEdit(gridWidget);
        massLine->setObjectName("massLine");

        grid->addWidget(massLine, 1, 0, 1, 1);

        myGLWidget = new GLWidget(gridWidget);
        myGLWidget->setObjectName("myGLWidget");
        myGLWidget->setEnabled(true);
        myGLWidget->setAcceptDrops(false);

        grid->addWidget(myGLWidget, 4, 0, 1, 1);

        ySpeedLine = new QLineEdit(gridWidget);
        ySpeedLine->setObjectName("ySpeedLine");

        grid->addWidget(ySpeedLine, 2, 0, 1, 1);

        clearButton = new QPushButton(gridWidget);
        clearButton->setObjectName("clearButton");

        grid->addWidget(clearButton, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 700, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
