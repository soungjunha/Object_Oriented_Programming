/********************************************************************************
** Form generated from reading UI file 'game_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_WINDOW_H
#define UI_GAME_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <board_widget.h>
#include "turn_indicator_widget.h"

QT_BEGIN_NAMESPACE

class Ui_game_window
{
public:
    board_widget *board;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *undo;
    QPushButton *go_to_start;
    turn_indicator_widget *turn_indicator;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *total_turn;
    QLabel *total_black;
    QLabel *total_white;

    void setupUi(QWidget *game_window)
    {
        if (game_window->objectName().isEmpty())
            game_window->setObjectName("game_window");
        game_window->resize(900, 675);
        board = new board_widget(game_window);
        board->setObjectName("board");
        board->setGeometry(QRect(10, 10, 650, 650));
        verticalLayoutWidget_2 = new QWidget(game_window);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(710, 580, 121, 61));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        undo = new QPushButton(verticalLayoutWidget_2);
        undo->setObjectName("undo");

        verticalLayout_2->addWidget(undo);

        go_to_start = new QPushButton(verticalLayoutWidget_2);
        go_to_start->setObjectName("go_to_start");

        verticalLayout_2->addWidget(go_to_start);

        turn_indicator = new turn_indicator_widget(game_window);
        turn_indicator->setObjectName("turn_indicator");
        turn_indicator->setGeometry(QRect(800, 20, 50, 50));
        verticalLayoutWidget = new QWidget(game_window);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(700, 50, 101, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        total_turn = new QLabel(verticalLayoutWidget);
        total_turn->setObjectName("total_turn");

        verticalLayout->addWidget(total_turn);

        total_black = new QLabel(verticalLayoutWidget);
        total_black->setObjectName("total_black");

        verticalLayout->addWidget(total_black);

        total_white = new QLabel(verticalLayoutWidget);
        total_white->setObjectName("total_white");

        verticalLayout->addWidget(total_white);


        retranslateUi(game_window);

        QMetaObject::connectSlotsByName(game_window);
    } // setupUi

    void retranslateUi(QWidget *game_window)
    {
        game_window->setWindowTitle(QCoreApplication::translate("game_window", "Form", nullptr));
        undo->setText(QCoreApplication::translate("game_window", "\353\220\230\353\217\214\353\246\254\352\270\260", nullptr));
        go_to_start->setText(QCoreApplication::translate("game_window", "\353\251\224\354\235\270\355\231\224\353\251\264", nullptr));
        total_turn->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
        total_black->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
        total_white->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_window: public Ui_game_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_WINDOW_H
