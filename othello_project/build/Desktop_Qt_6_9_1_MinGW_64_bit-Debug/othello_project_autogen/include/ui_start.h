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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_start
{
public:
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *new_game;
    QPushButton *continue_game;
    QPushButton *load_game;
    QPushButton *replay;
    QPushButton *quit;

    void setupUi(QWidget *start)
    {
        if (start->objectName().isEmpty())
            start->setObjectName("start");
        start->resize(900, 675);
        label = new QLabel(start);
        label->setObjectName("label");
        label->setGeometry(QRect(390, 220, 121, 41));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        horizontalLayoutWidget = new QWidget(start);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(150, 310, 581, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        new_game = new QPushButton(horizontalLayoutWidget);
        new_game->setObjectName("new_game");
        new_game->setMinimumSize(QSize(111, 41));

        horizontalLayout->addWidget(new_game);

        continue_game = new QPushButton(horizontalLayoutWidget);
        continue_game->setObjectName("continue_game");
        continue_game->setMinimumSize(QSize(111, 41));

        horizontalLayout->addWidget(continue_game);

        load_game = new QPushButton(horizontalLayoutWidget);
        load_game->setObjectName("load_game");
        load_game->setMinimumSize(QSize(111, 41));

        horizontalLayout->addWidget(load_game);

        replay = new QPushButton(horizontalLayoutWidget);
        replay->setObjectName("replay");
        replay->setMinimumSize(QSize(111, 41));

        horizontalLayout->addWidget(replay);

        quit = new QPushButton(horizontalLayoutWidget);
        quit->setObjectName("quit");
        quit->setMinimumSize(QSize(111, 41));

        horizontalLayout->addWidget(quit);


        retranslateUi(start);

        QMetaObject::connectSlotsByName(start);
    } // setupUi

    void retranslateUi(QWidget *start)
    {
        start->setWindowTitle(QCoreApplication::translate("start", "Form", nullptr));
        label->setText(QCoreApplication::translate("start", "OTHELLO", nullptr));
        new_game->setText(QCoreApplication::translate("start", "\354\203\210 \352\262\214\354\236\204", nullptr));
        continue_game->setText(QCoreApplication::translate("start", "\354\235\264\354\226\264\355\225\230\352\270\260", nullptr));
        load_game->setText(QCoreApplication::translate("start", "\353\266\210\353\237\254\354\230\244\352\270\260", nullptr));
        replay->setText(QCoreApplication::translate("start", "\353\246\254\355\224\214\353\240\210\354\235\264", nullptr));
        quit->setText(QCoreApplication::translate("start", "\352\262\214\354\236\204 \354\242\205\353\243\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class start: public Ui_start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
