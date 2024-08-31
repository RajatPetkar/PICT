/********************************************************************************
** Form generated from reading UI file 'koch_curve.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KOCH_CURVE_H
#define UI_KOCH_CURVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_koch_curve
{
public:
    QWidget *centralwidget;
    QLabel *display;
    QPushButton *create;
    QPlainTextEdit *level;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *koch_curve)
    {
        if (koch_curve->objectName().isEmpty())
            koch_curve->setObjectName(QString::fromUtf8("koch_curve"));
        koch_curve->resize(800, 600);
        centralwidget = new QWidget(koch_curve);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        display = new QLabel(centralwidget);
        display->setObjectName(QString::fromUtf8("display"));
        display->setGeometry(QRect(0, 0, 500, 500));
        create = new QPushButton(centralwidget);
        create->setObjectName(QString::fromUtf8("create"));
        create->setGeometry(QRect(600, 320, 103, 36));
        level = new QPlainTextEdit(centralwidget);
        level->setObjectName(QString::fromUtf8("level"));
        level->setGeometry(QRect(600, 180, 104, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(610, 150, 91, 20));
        koch_curve->setCentralWidget(centralwidget);
        menubar = new QMenuBar(koch_curve);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        koch_curve->setMenuBar(menubar);
        statusbar = new QStatusBar(koch_curve);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        koch_curve->setStatusBar(statusbar);

        retranslateUi(koch_curve);

        QMetaObject::connectSlotsByName(koch_curve);
    } // setupUi

    void retranslateUi(QMainWindow *koch_curve)
    {
        koch_curve->setWindowTitle(QApplication::translate("koch_curve", "koch_curve", nullptr));
        display->setText(QApplication::translate("koch_curve", "display", nullptr));
        create->setText(QApplication::translate("koch_curve", "Create", nullptr));
        label->setText(QApplication::translate("koch_curve", "No. of Levels", nullptr));
    } // retranslateUi

};

namespace Ui {
    class koch_curve: public Ui_koch_curve {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KOCH_CURVE_H
