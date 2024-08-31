/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;
    QLabel *label_2;
    QTextEdit *textEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *textEdit_3;
    QLabel *label_5;
    QPushButton *pushButton_3;
    QTextEdit *textEdit_4;
    QTextEdit *textEdit_5;
    QPushButton *pushButton_4;
    QTextEdit *textEdit_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 400, 400));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(500, 10, 181, 25));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(500, 40, 181, 25));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(510, 90, 61, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(500, 90, 16, 17));
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(600, 90, 61, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(590, 90, 16, 17));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(680, 70, 111, 17));
        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(680, 90, 61, 31));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(510, 70, 161, 17));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(500, 170, 89, 25));
        textEdit_4 = new QTextEdit(centralwidget);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setGeometry(QRect(600, 170, 51, 21));
        textEdit_5 = new QTextEdit(centralwidget);
        textEdit_5->setObjectName(QString::fromUtf8("textEdit_5"));
        textEdit_5->setGeometry(QRect(660, 170, 51, 21));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(500, 210, 89, 25));
        textEdit_6 = new QTextEdit(centralwidget);
        textEdit_6->setObjectName(QString::fromUtf8("textEdit_6"));
        textEdit_6->setGeometry(QRect(600, 210, 51, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Show Co-ordinate System", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Plot Eq Triangle", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "x", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "y", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "lenght of side", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "First Vetrex of triangle", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Translate", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Rotate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
