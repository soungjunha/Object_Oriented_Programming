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

QT_BEGIN_NAMESPACE

class Ui_game_window
{
public:
    board_widget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *total_turn;
    QLabel *label_2;
    QLabel *black_total_turn;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *back_turn;
    QPushButton *go_to_start;
    QWidget *widget_2;
    QLabel *size;
    QLabel *ob;
    QLabel *fr;

    void setupUi(QWidget *game_window)
    {
        if (game_window->objectName().isEmpty())
            game_window->setObjectName("game_window");
        game_window->resize(900, 675);
        widget = new board_widget(game_window);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 651, 651));
        verticalLayoutWidget = new QWidget(game_window);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(700, 50, 101, 151));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        total_turn = new QLabel(verticalLayoutWidget);
        total_turn->setObjectName("total_turn");

        verticalLayout->addWidget(total_turn);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        black_total_turn = new QLabel(verticalLayoutWidget);
        black_total_turn->setObjectName("black_total_turn");

        verticalLayout->addWidget(black_total_turn);

        verticalLayoutWidget_2 = new QWidget(game_window);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(710, 580, 121, 61));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        back_turn = new QPushButton(verticalLayoutWidget_2);
        back_turn->setObjectName("back_turn");

        verticalLayout_2->addWidget(back_turn);

        go_to_start = new QPushButton(verticalLayoutWidget_2);
        go_to_start->setObjectName("go_to_start");

        verticalLayout_2->addWidget(go_to_start);

        widget_2 = new QWidget(game_window);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(780, 20, 50, 50));
        size = new QLabel(game_window);
        size->setObjectName("size");
        size->setGeometry(QRect(720, 260, 48, 16));
        ob = new QLabel(game_window);
        ob->setObjectName("ob");
        ob->setGeometry(QRect(730, 310, 48, 16));
        fr = new QLabel(game_window);
        fr->setObjectName("fr");
        fr->setGeometry(QRect(790, 390, 48, 16));

        retranslateUi(game_window);

        QMetaObject::connectSlotsByName(game_window);
    } // setupUi

    void retranslateUi(QWidget *game_window)
    {
        game_window->setWindowTitle(QCoreApplication::translate("game_window", "Form", nullptr));
        total_turn->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
        black_total_turn->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
        back_turn->setText(QCoreApplication::translate("game_window", "\353\220\230\353\217\214\353\246\254\352\270\260", nullptr));
        go_to_start->setText(QCoreApplication::translate("game_window", "\353\251\224\354\235\270\355\231\224\353\251\264", nullptr));
        size->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
        ob->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
        fr->setText(QCoreApplication::translate("game_window", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_window: public Ui_game_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_WINDOW_H
