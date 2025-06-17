/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_start
{
public:
    QPushButton *replay;
    QPushButton *CONTINUE;
    QPushButton *quit;
    QLabel *label;
    QPushButton *new_game;

    void setupUi(QWidget *start)
    {
        if (start->objectName().isEmpty())
            start->setObjectName("start");
        start->resize(1200, 675);
        replay = new QPushButton(start);
        replay->setObjectName("replay");
        replay->setGeometry(QRect(580, 350, 111, 41));
        CONTINUE = new QPushButton(start);
        CONTINUE->setObjectName("CONTINUE");
        CONTINUE->setGeometry(QRect(430, 350, 111, 41));
        quit = new QPushButton(start);
        quit->setObjectName("quit");
        quit->setGeometry(QRect(730, 350, 111, 41));
        label = new QLabel(start);
        label->setObjectName("label");
        label->setGeometry(QRect(510, 190, 121, 41));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        new_game = new QPushButton(start);
        new_game->setObjectName("new_game");
        new_game->setGeometry(QRect(290, 350, 111, 41));

        retranslateUi(start);

        QMetaObject::connectSlotsByName(start);
    } // setupUi

    void retranslateUi(QWidget *start)
    {
        start->setWindowTitle(QCoreApplication::translate("start", "Form", nullptr));
        replay->setText(QCoreApplication::translate("start", "REPLAY", nullptr));
        CONTINUE->setText(QCoreApplication::translate("start", "CONTINUE", nullptr));
        quit->setText(QCoreApplication::translate("start", "QUIT", nullptr));
        label->setText(QCoreApplication::translate("start", "OTHELLO", nullptr));
        new_game->setText(QCoreApplication::translate("start", "NEW GAME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class start: public Ui_start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
