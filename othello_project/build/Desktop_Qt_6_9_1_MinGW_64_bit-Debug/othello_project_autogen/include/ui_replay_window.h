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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_replay_window
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *total_turn;
    QLabel *label_2;
    QLabel *black_total_turn;
    QWidget *widget_2;
    QWidget *widget;
    QPushButton *go_to_start;

    void setupUi(QWidget *replay_window)
    {
        if (replay_window->objectName().isEmpty())
            replay_window->setObjectName("replay_window");
        replay_window->resize(900, 675);
        verticalLayoutWidget = new QWidget(replay_window);
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

        widget_2 = new QWidget(replay_window);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(780, 20, 50, 50));
        widget = new QWidget(replay_window);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 651, 651));
        go_to_start = new QPushButton(replay_window);
        go_to_start->setObjectName("go_to_start");
        go_to_start->setGeometry(QRect(710, 620, 119, 24));

        retranslateUi(replay_window);

        QMetaObject::connectSlotsByName(replay_window);
    } // setupUi

    void retranslateUi(QWidget *replay_window)
    {
        replay_window->setWindowTitle(QCoreApplication::translate("replay_window", "Form", nullptr));
        total_turn->setText(QCoreApplication::translate("replay_window", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("replay_window", "TextLabel", nullptr));
        black_total_turn->setText(QCoreApplication::translate("replay_window", "TextLabel", nullptr));
        go_to_start->setText(QCoreApplication::translate("replay_window", "\353\251\224\354\235\270\355\231\224\353\251\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class replay_window: public Ui_replay_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLAY_WINDOW_H
