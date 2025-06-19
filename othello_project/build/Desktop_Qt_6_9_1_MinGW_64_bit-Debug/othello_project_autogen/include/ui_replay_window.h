/********************************************************************************
** Form generated from reading UI file 'replay_window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLAY_WINDOW_H
#define UI_REPLAY_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <board_widget.h>

QT_BEGIN_NAMESPACE

class Ui_replay_window
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *total_turn;
    QLabel *total_white;
    QLabel *total_black;
    board_widget *board;
    QPushButton *go_to_start;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *prev_turn;
    QSlider *turn;
    QPushButton *next_turn;

    void setupUi(QWidget *replay_window)
    {
        if (replay_window->objectName().isEmpty())
            replay_window->setObjectName("replay_window");
        replay_window->resize(900, 675);
        verticalLayoutWidget = new QWidget(replay_window);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(700, 50, 141, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        total_turn = new QLabel(verticalLayoutWidget);
        total_turn->setObjectName("total_turn");

        verticalLayout->addWidget(total_turn);

        total_white = new QLabel(verticalLayoutWidget);
        total_white->setObjectName("total_white");

        verticalLayout->addWidget(total_white);

        total_black = new QLabel(verticalLayoutWidget);
        total_black->setObjectName("total_black");

        verticalLayout->addWidget(total_black);

        board = new board_widget(replay_window);
        board->setObjectName("board");
        board->setGeometry(QRect(10, 10, 600, 600));
        go_to_start = new QPushButton(replay_window);
        go_to_start->setObjectName("go_to_start");
        go_to_start->setGeometry(QRect(710, 620, 119, 24));
        horizontalLayoutWidget = new QWidget(replay_window);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 620, 601, 42));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        prev_turn = new QPushButton(horizontalLayoutWidget);
        prev_turn->setObjectName("prev_turn");
        prev_turn->setMinimumSize(QSize(40, 40));
        prev_turn->setMaximumSize(QSize(40, 40));
        QFont font;
        font.setPointSize(25);
        prev_turn->setFont(font);

        horizontalLayout->addWidget(prev_turn);

        turn = new QSlider(horizontalLayoutWidget);
        turn->setObjectName("turn");
        turn->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(turn);

        next_turn = new QPushButton(horizontalLayoutWidget);
        next_turn->setObjectName("next_turn");
        next_turn->setMinimumSize(QSize(40, 40));
        next_turn->setMaximumSize(QSize(40, 40));
        next_turn->setFont(font);

        horizontalLayout->addWidget(next_turn);


        retranslateUi(replay_window);

        QMetaObject::connectSlotsByName(replay_window);
    } // setupUi

    void retranslateUi(QWidget *replay_window)
    {
        replay_window->setWindowTitle(QCoreApplication::translate("replay_window", "Form", nullptr));
        total_turn->setText(QCoreApplication::translate("replay_window", "TextLabel", nullptr));
        total_white->setText(QCoreApplication::translate("replay_window", "TextLabel", nullptr));
        total_black->setText(QCoreApplication::translate("replay_window", "TextLabel", nullptr));
        go_to_start->setText(QCoreApplication::translate("replay_window", "\353\251\224\354\235\270\355\231\224\353\251\264", nullptr));
        prev_turn->setText(QCoreApplication::translate("replay_window", "\342\206\220", nullptr));
        next_turn->setText(QCoreApplication::translate("replay_window", "\342\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class replay_window: public Ui_replay_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLAY_WINDOW_H
